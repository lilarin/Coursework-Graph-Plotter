//
// Created by User on 29.04.2022.
//


#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

enum Token_type
{
    NUMBER,
    OPERATOR,
    BRACKET,
    FUNCTION,
    CONSTANT
};

struct Token
{
    Token_type type;
    string value;
};

vector <Token> parse(const string& expression)
{
    vector <Token> tokens;
    string digits;
    string letters;

    for (unsigned int i = 0; i < expression.size(); ++i)
    {
        char character = expression[i];

        if (character == ' ') continue;

        if (isdigit(character) || character == '.')
            digits.push_back(character);

        else if (isalpha(character))
            letters.push_back(character);

        else if (character == ',')
        {
            Token sign;
            if (digits != "")
            {
                sign.type = Token_type::NUMBER;
                sign.value = digits;
                tokens.push_back(sign);
                digits = "";
            }
            if (letters != "")
            {
                sign.type = Token_type::CONSTANT;
                sign.value = letters;
                tokens.push_back(sign);
                letters = "";
            }
        }

        else if ((character == '+') || (character == '-') || (character == '*') || (character == '/') || (character == '^'))
        {
            Token sign;
            if (digits != "")
            {
                sign.type = Token_type::NUMBER;
                sign.value = digits;
                tokens.push_back(sign);
                digits = "";
            }
            if (letters != "")
            {
                sign.type = Token_type::CONSTANT;
                sign.value = letters;
                tokens.push_back(sign);
                letters = "";
            }
            sign.type = Token_type::OPERATOR;
            sign.value = character;
            tokens.push_back(sign);
        }
        else if (character == '(')
        {
            Token bracket;
            if (letters != "")
            {
                bracket.type = Token_type::FUNCTION;
                bracket.value = letters;
                tokens.push_back(bracket);
                letters = "";
            }
            bracket.type = Token_type::BRACKET;
            bracket.value = character;
            tokens.push_back(bracket);
        }
        else if (character == ')')
        {
            Token sign;
            if (digits != "")
            {
                sign.type = Token_type::NUMBER;
                sign.value = digits;
                tokens.push_back(sign);
                digits = "";
            }
            if (letters != "")
            {
                sign.type = Token_type::CONSTANT;
                sign.value = letters;
                tokens.push_back(sign);
                letters = "";
            }
            sign.type = Token_type::BRACKET;
            sign.value = character;
            tokens.push_back(sign);
        }
        else
        {
            cout << "pizdes" << endl;
        }
    }

    Token token;
    if (digits != "")
    {
        token.type = Token_type::NUMBER;
        token.value = digits;
        tokens.push_back(token);
    }
    if (letters != "")
    {
        token.type = Token_type::CONSTANT;
        token.value = letters;
        tokens.push_back(token);
    }
    return tokens;
}

vector <Token> negative_numbers(vector <Token>& tokens)
{
    vector <Token> tokens_;

    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        Token symbol = tokens[i];

        if (symbol.type == Token_type::NUMBER)
            tokens_.push_back(symbol);

        if (symbol.type == Token_type::BRACKET)
            tokens_.push_back(symbol);

        if (symbol.type == Token_type::FUNCTION)
            tokens_.push_back(symbol);

        else if ((symbol.type == Token_type::OPERATOR) || (symbol.type == Token_type::CONSTANT))
        {
            if (((tokens_.empty()) || (tokens_.back().value == "(")) && symbol.value == "-")
            {
                Token token;
                token.type = Token_type::NUMBER;
                token.value = "0";

                tokens_.push_back(token);
                tokens_.push_back(symbol);
            }
            else
                tokens_.push_back(symbol);
        }
    }
    return tokens_;
}

int check(Token symbol)
{
    if ((symbol.value == "+") || (symbol.value == "-")) return 1;
    if ((symbol.value == "*") || (symbol.value == "/")) return 2;
    if (symbol.value == "^") return 3;
    return 0;
}

queue <Token> RPN(const vector <Token>& tokens)
{
    queue <Token> output;
    stack <Token> stack_;

    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        Token symbol = tokens[i];

        if ((symbol.type == Token_type::NUMBER) || (symbol.type == Token_type::CONSTANT))
            output.push(symbol);

        if (symbol.type == Token_type::FUNCTION)
            stack_.push(symbol);

        if (symbol.type == Token_type::OPERATOR)
        {
            while ((!stack_.empty()) && (stack_.top().value != "(") && ((stack_.top().type == Token_type::FUNCTION) || (check(stack_.top()) >= check(symbol))))
            {
                output.push(stack_.top());
                stack_.pop();
            }
            stack_.push(symbol);
        }

        if (symbol.value == "(")
            stack_.push(symbol);

        if (symbol.value == ")")
        {
            while (stack_.top().value != "(")
            {
                output.push(stack_.top());
                stack_.pop();
            }
            if (stack_.top().value == "(")
                stack_.pop();
        }
    }
    while(!stack_.empty())
    {
        output.push(stack_.top());
        stack_.pop();
    }
    return output;
}

double stack_calc(queue <Token>& rpn_tokens, double x)
{
    double result = 0;
    stack <double> stack_;

    while (!rpn_tokens.empty())
    {
        Token token = rpn_tokens.front();

        if (token.type == Token_type::NUMBER)
        {
            double number = stof(token.value);
            stack_.push(number);
        }
        else if (token.type == Token_type::CONSTANT)
        {
            double constant;
            if (token.value == "e")
            {
                constant = M_E;
                stack_.push(constant);
            }
            if (token.value == "x")
            {
                constant = x;
                stack_.push(constant);
            }
            if (token.value == "pi")
            {
                constant = M_PI;
                stack_.push(constant);
            }
        }
        else if (token.type == Token_type::OPERATOR)
        {
            double a = stack_.top();
            stack_.pop();

            double b = stack_.top();
            stack_.pop();

            if (token.value == "+")
                stack_.push(a + b);

            if (token.value == "-")
                stack_.push(b - a);

            if (token.value == "*")
                stack_.push(a * b);

            if (token.value == "/")
                stack_.push(b / a);

            if (token.value == "^")
                stack_.push(pow(b, a));
        }
        else if (token.type == Token_type::FUNCTION && token.value == "log")
        {
            double a = stack_.top();
            stack_.pop();

            double b = stack_.top();
            stack_.pop();

            stack_.push(log(a) / log(b));
        }
        else if (token.type == Token_type::FUNCTION)
        {
            double c = stack_.top();
            stack_.pop();

            if (token.value == "sqrt")
                stack_.push(sqrt(c));

            if (token.value == "sin")
                stack_.push(sin(c));

            if (token.value == "cos")
                stack_.push(cos(c));

            if (token.value == "tan")
                stack_.push((sin(c) / cos(c)));

            if (token.value == "cot")
                stack_.push((cos(c) / sin(c)));

            if (token.value == "ln")
                stack_.push((log(c)));

        }
        rpn_tokens.pop();
    }
    result = stack_.top();
    return result;
}

double evaluate(string& expression,double x)
{
    vector <Token> tokens = parse(expression);
    vector <Token> tokens_ = negative_numbers(tokens);
    queue <Token> rpn_tokens = RPN(tokens_);
    return stack_calc(rpn_tokens,x);
}

