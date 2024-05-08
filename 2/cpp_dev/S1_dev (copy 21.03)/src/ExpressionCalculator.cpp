#include "ExpressionCalculator.h"
#include <string>
#include <cctype>
#include "Stack.hpp"

ExpressionCalculator::ExpressionCalculator(const std::string &expr)
{
    exprToLexemes(expr);
}

long long ExpressionCalculator::solve() const
{
    Queue<std::string> postfixExpr = postfixForm(lexemes_);

    Stack<long long> values;
    for (std::string lexeme = postfixExpr.drop();; lexeme = postfixExpr.drop())
    {

        if (isdigit(lexeme[0]))
        {
            values.push(std::stoll(lexeme));
        }
        else
        {

            long long right = values.drop();
            long long left = values.drop();
            long long res;
            switch (lexeme[0])
            {
            case '+':
                res = left + right;
                if ((left <= res) && (right <= res))
                {
                    values.push(res);
                }
                else
                {
                    throw std::overflow_error("long long overflow occured (addition)");
                }
                break;
            case '-':
                res = left - right;
                if ((left >= res))
                {
                    values.push(res);
                }
                else
                {
                    throw std::overflow_error("long long overflow occured (subtraction)");
                }
                break;
                break;
            case '/':
                values.push(left / right);
                break;
            case '*':
                res = left * right;
                if (res / left * left == res / right * right)
                {
                    values.push(res);
                }
                else
                {
                    throw std::overflow_error("long long overflow occured (multiplication)");
                }
                break;
            case '%':
                values.push((left < 0) ? (right - (abs(left) % right)) : left % right);
                break;
            default:
                throw std::logic_error("Unknown operator! (solve)");
            }
        }
        if (postfixExpr.isEmpty())
        {
            break;
        }
    }

    long long res = values.drop();
    if (!values.isEmpty())
    {
        throw std::logic_error("Bad expression! (solve)");
    }

    return res;
}

void ExpressionCalculator::exprToLexemes(const std::string &expr)
{
    std::string res = "";
    for (std::size_t i = 0; i < expr.length(); i++)
    {
        std::string lexeme = "";
        if (expr[i] != ' ')
        {
            if (isdigit(expr[i]))
            {
                for (; (expr[i] != ' ') && (i < expr.length()) && isdigit(expr[i]); i++)
                {
                    lexeme.append(std::string(1, expr[i]));
                }
                i--;
                lexemes_.push(lexeme);
            }
            else
            {
                lexeme.append(std::string(1, expr[i]));
                lexemes_.push(lexeme);
            }
        }
    }
}

int ExpressionCalculator::order(const char &op)
{
    switch (op)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '%':
        return 2;

    default:
        return 0;
    }
}

bool ExpressionCalculator::isHigher(const char &a, const char &b)
{
    if (order(a) >= order(b))
        return true;
    else
        return false;
}

Queue<std::string> ExpressionCalculator::postfixForm(Queue<std::string> lexemes) const
{
    Stack<std::string> stk;
    Queue<std::string> postfix_tokens;
    stk.push("(");
    lexemes.push(")");

    while (!lexemes.isEmpty())
    {

        std::string token = lexemes.drop();

        if (token == "(")
        {
            stk.push(token);
        }
        else if (token == ")")
        {

            // Pop out all the operators and append them to postfix expression till an opening bracket is found
            while (stk.peek() != "(")
            {
                postfix_tokens.push(stk.drop());
            }
            stk.drop();
        }
        else if (token == "*" || token == "/" || token == "+" || token == "-" || token == "%")
        {

            // Pop out operators with higher precedence at the top of the stack and append them to
            // the postfix expression, before pushing the current operator to the stack.
            while (!stk.isEmpty() && order(stk.peek()[0]) >= order(token[0]))
            {
                postfix_tokens.push(stk.drop());
            }
            stk.push(token);
        }
        else
        {
            // Positions of the operands do not change in the postfix expression so append
            // an operand as it is.
            postfix_tokens.push(token);
        }
    }

    if (!stk.isEmpty())
    {
        throw std::logic_error("too many operators!");
    }

    return postfix_tokens;
}
