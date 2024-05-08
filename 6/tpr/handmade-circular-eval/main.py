import os 
import typing as tp
from pprint import pprint

from openai import OpenAI
from tqdm import tqdm


questions = [
    {
        "image_link": "https://images6.fanpop.com/image/photos/35800000/Puppy-dogs-35894603-1920-1200.jpg",
        "question": "What animal is on the image?",
        "answers": ["a bird", "a dog", "a cat", "not an animal"],
        "gt_answer": "a dog"
    },
    {
        "image_link": "https://upload.wikimedia.org/wikipedia/commons/a/a5/Red_Kitten_01.jpg",
        "question": "What animal is on the image?",
        "answers": ["a bird", "a dog", "a cat", "not an animal"],
        "gt_answer": "a cat"
    },
    {
        "image_link": "https://i.insider.com/58fe49fb0ba0b8ea048b59e9?width=2400",
        "question": "What animal is on the image?",
        "answers": ["a bird", "a dog", "a cat", "not an animal"],
        "gt_answer": "not an animal"
    },
]

def get_sample(q_text: str, answers: tp.List[str], gt: str, image_link: tp.Optional[str] = "") -> tp.Tuple[str,str]:
    LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    assert gt in answers, "GT is not in answers."

    gt_letter = LETTERS[answers.index(gt)]
    choices = [f'{LETTERS[i]}. {answer}' for i, answer in enumerate(answers)]
    choices_text = "; ".join(choices) + '.'
    sample = f'Q: {q_text}\nChoices: {choices_text}'

    return {
        "prompt": sample, 
        "q_text": q_text,
        "options_text": choices_text,
        "gt_letter": gt_letter, 
        "image_link": image_link
    }

def get_shifted_answers(answers) -> tp.List[tp.List[str]]:
    results = []
    answers_len = len(answers)
    for i in range(1, answers_len):
        shifted_answers = [] 
        for j in range(i, answers_len):
            shifted_answers.append(answers[j])
        for j in range(0, i):
            shifted_answers.append(answers[j])
        results.append(shifted_answers)
    results = results[::-1]
    results = [answers, ] + results
    return results

def extract_model_choice(question: str, options: str, prediction: str, evaluator_client):
    gpt_query_template = (
        "You are an AI assistant to help me matching an answer with several options of a multiple choice question. "
        "You are provided with a question, several options, and an answer, "
        "and you need to find which option is most similar to the answer. "
        "If the meaning of all options are significantly different from the answer, output X. "\
        "Your should output a single uppercase character in A, B, C, D (if they are valid options), and X. \n"
        "Example 1: \n"
        "Question: What is the main object in image?\nOptions: A. teddy bear B. rabbit C. cat D. dog\n"
        "Answer: a cute teddy bear\nYour output: A\n"
        "Example 2: \n"
        "Question: What is the main object in image?\nOptions: A. teddy bear B. rabbit C. cat D. dog\n"
        "Answer: Spider\nYour output: X\n"
        "Example 3: \n"
        f"Question: {question}?\nOptions: {options}\nAnswer: {prediction}\nYour output: "
    )
    prompt = gpt_query_template.replace('{question}', question).replace('{options}', options).replace('{prediction}', prediction)
    completion = evaluator_client.completions.create(
      model="i don't care",
      prompt=prompt,
      max_tokens=10, # because we await A, B, C, D or X.
      temperature=0.1,
      stop='\n',
    )
    answer = completion.content.strip()
    assert len(answer) >= 1
    return answer[0]


def get_model_response(question: str, options: str, image_url: str, evaluatee_client) -> str:
    template = (
        "You are an AI assistant to be evaluated by a benchmark. "
        "You are provided with a question, several options, "
        "and you need to choose an option which is best answers a questions based on image and question you get."
        "Your should output a single uppercase character in A, B, C, D (if they are valid options), and X. \n"
        f"Question: {question}?\nOptions: {options}\nYour answer: "
    )
    prompt = template.replace("{question}", question).replace('{options}', options)
    completion = evaluatee_client.chat.completions.create(
      model="i don't care (VL)",
      messages=[
        {
          "role": "user",
          "content": [
            {"type": "text", "text": prompt },
            {
              "type": "image_url",
              "image_url": {
                "url": image_url,
              },
            },
          ],
        }
      ],
      max_tokens=300,
    )
    answer = completion.choices[0].message.content
    return answer 

def circular_eval_single(q: dict, evaluatee_client, evaluator_client, verbose: bool = True) -> bool:
    """
        Performs circular eval on a question of format
        question = {
            "image_link": "https://techbriefly.com/wp-content/uploads/2021/01/ddg2.jpg",
            "quesiton": "What animal is displayed on DuckDuckGo logo?",
            "answers": ["a bird", "a dog", "a cat", "not an animal"]
            "gt_answer": "a bird"
        }

        If necessary, it loads the image and then feeds it to the multi-modal model.
    """
    assert 'question' in q 
    assert 'answers' in q
    assert 'gt_answer' in q
    assert 'image_link' in q
    assert q['gt_answer'] in q['answers']
    assert len(q['answers']) > 1 and len(q['answers']) < 5

    image_link = q.get('image_link', "")
    q_text = q['question']
    answers = q['answers']
    gt_answer = q['gt_answer']

    shifted_answers_lists = get_shifted_answers(answers)

    passes = []
    for shifted_answers in shifted_answers_lists:
        pass_item = get_sample(q_text, shifted_answers, gt_answer, image_link)
        passes.append(pass_item)

    for i, p in enumerate(tqdm(passes, desc='passes', disable=not verbose)):
        q_text = p['q_text']
        options_text = p['options_text']
        gt_letter = p['gt_letter']
        image_link = p['image_link']

        if verbose: 
            print("="*80)
            print(f"Q: {q_text}\nImage link:{image_link}\nOptions: {options_text}\nGT: {gt_letter}")

        model_response = get_model_response(q_text, options_text, image_link, evaluatee_client)
        if verbose: 
            print(f"Model Raw: {model_response}")

        model_evaluated = extract_model_choice(q_text, options_text, model_response, evaluator_client)

        if verbose:
            print(f"Extracted model choice: {model_evaluated}")

        assert model_evaluated in ["A", "B", "C", "D", "X"], model_evaluated    
        
        if gt_letter.lower() != model_evaluated.lower():
            if verbose:
                print(f"Failed at pass {i}")

            return False
        
    return True




if __name__ == "__main__":
    OAI_EVALUATOR_API = os.getenv("OAI_EVALUATOR_API", "http://localhost:6969/v1")
    OAI_EVALUATEE_API = os.getenv("OAI_EVALUATEE_API", "http://localhost:4242/v1")

    evaluatee_client = OpenAI(base_url=OAI_EVALUATEE_API, api_key="i_dont_care")
    evaluator_client = OpenAI(base_url=OAI_EVALUATOR_API, api_key="i_dont_care")

    
    correct = 0
    for q in tqdm(questions, desc='Questions'):
        answer = circular_eval_single(q, evaluatee_client, evaluator_client)
        print(f'CircularEval verdict: {answer}')
        if answer:
            correct += 1
    print("="*80)
    print("SUMMARY")
    print(f"\tTotal: {len(questions)}")
    print(f"\tCorrect: {correct}")
    print(f"\tScore: {100 * correct/len(questions):.2f}")
    



