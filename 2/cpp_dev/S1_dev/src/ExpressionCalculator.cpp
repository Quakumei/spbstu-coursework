#include <sstream>
#include <cctype>

#include "Stack.hpp"
#include "Queue.hpp"

#include "ExpressionCalculator.h"
#include "Tokenize.h"

namespace tampio
{
    ExpressionCalculator::ExpressionCalculator(const std::string &expression)
    {
        lexemes_ = postfixForm(convertToLexemes(expression));
    }

    long long ExpressionCalculator::solve() const
    {
        Queue< std::string > postfixExpr = lexemes_;
        Stack< long long > values;

        std::string lexeme = "";
        while (!postfixExpr.isEmpty())
        {
            lexeme = postfixExpr.peek();
            postfixExpr.rm_back();
            if (isdigit(lexeme[0]))
            {
                values.push(std::stoll(lexeme));
                continue;
            }

            long long right = values.peek();
            values.rm_back();
            long long left = values.peek();
            values.rm_back();

            long long res = 0;
            char op = lexeme[0];
            switch (op)
            {
            case '+':
                res = left + right;
                if (!((left <= res) || (right <= res)))
                {
                    throw std::overflow_error("long long overflow occured (addition)");
                }
                break;

            case '-':
                res = left - right;
                if (!(left >= res))
                {
                    throw std::overflow_error("long long overflow occured (subtraction)");
                }
                break;

            case '*':
                res = left * right;
                if (!(res / left * left == res / right * right))
                {
                    throw std::overflow_error("long long overflow occured (multiplication)");
                }
                break;

            case '/':
                res = left / right;
                break;

            case '%':
                res = (left < 0) ? (right - (abs(left) % right)) : left % right;
                break;

            default:
                std::stringstream ss;
                ss << "Unknown operator --> '" << op << "' <-- solve()";
                throw std::logic_error(ss.str().c_str());
            }
            values.push(res);
        }

        long long res = values.peek();
        values.rm_back();
        if (!values.isEmpty())
        {
            throw std::logic_error("Bad expression! (solve)");
        }

        return res;
    }

    ExpressionCalculator::Priority ExpressionCalculator::order(const char &op)
    {
        switch (op)
        {
        case '(':
        case ')':
            return PRIORITY_PARENTHESIS;
        case '+':
        case '-':
            return PRIORITY_ADDITION;
        case '*':
        case '/':
        case '%':
            return PRIORITY_MULTIPLICATION;

        default:
            throw std::logic_error("Unknown operator!");
        }
    }

    bool ExpressionCalculator::isHigher(const char &a, const char &b)
    {
        return order(a) >= order(b);
    }

    Queue<std::string > ExpressionCalculator::postfixForm(Queue< std::string > lexemes) const
    {
        Stack< std::string > stack;
        Queue< std::string > postfix_tokens;
        stack.push("(");
        lexemes.push(")");

        while (!lexemes.isEmpty())
        {
            std::string token = lexemes.peek();
            lexemes.rm_back();
            if (token == "(")
            {
                stack.push(token);
            }
            else if (token == ")")
            {
                while (stack.peek() != "(")
                {
                    postfix_tokens.push(stack.peek());
                    stack.rm_back();
                }
                stack.peek();
                stack.rm_back();
            }
            else if (OPERATORS_.find(token) != std::string::npos)
            {
                while (!stack.isEmpty() && isHigher(stack.peek()[0], token[0]))
                {
                    postfix_tokens.push(stack.peek());
                    stack.rm_back();
                }
                stack.push(token);
            }
            else
            {
                postfix_tokens.push(token);
            }
        }
        if (!stack.isEmpty())
        {
            throw std::logic_error("Too many operators!");
        }
        return postfix_tokens;
    }

}
