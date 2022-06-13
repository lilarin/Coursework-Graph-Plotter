//
// Created by User on 09.06.2022.
//

#ifndef MAIN_CPP_UTILITY_H
#define MAIN_CPP_UTILITY_H
#include <sstream>
#include "shunting_yard.h"

float roundValue(float number) {   // round the number down to a hundredth
    float value = (int)(number * 100 + .5);
    return value / 100;
}

string numberToString(float number) {
    stringstream ss;    // create a stringstream
    string str;         // create string
    ss << number;       // add number to the stream
    ss >> str;          // push the contents onto a string
    return str;         // return the string
}

double stack_calc(queue<Token>& rpn_tokens, double x) { // here the values are taken out one by one,
    double result;                                       // and the solution stays on the stack at the top
    stack <double> stack_;

    while (!rpn_tokens.empty()) {
        Token token = rpn_tokens.front();

        if (token.type == Token_type::NUMBER) {
            double number = stof(token.value);
            stack_.push(number);
        }
        else if (token.type == Token_type::CONSTANT) {
            double constant;
            if (token.value == "e") {
                constant = M_E;
                stack_.push(constant);
            }

            if (token.value == "x" || token.value == "X") { // additional ability to using uppercase X
                constant = x;                               // This can also be done for all constants and
                stack_.push(constant);                      // functions, but I don't see the point.
            }

            if (token.value == "pi") {
                constant = M_PI;
                stack_.push(constant);
            }
        }
        else if (token.type == Token_type::OPERATOR) {
            double a = stack_.top();
            stack_.pop();

            double b = stack_.top();
            stack_.pop();

            if (token.value == "+") {
                stack_.push(a + b);
            }

            if (token.value == "-") {
                stack_.push(b - a);
            }

            if (token.value == "*") {
                stack_.push(a * b);
            }

            if (token.value == "/") {
                stack_.push(b / a);
            }

            if (token.value == "^") {
                stack_.push(pow(b, a));
            }
        }
        else if (token.type == Token_type::FUNCTION) {
            double c = stack_.top();
            stack_.pop();

            if (token.value == "sqrt") {
                stack_.push(sqrt(c));
            }

            if (token.value == "sin") {
                stack_.push(sin(c));
            }

            if (token.value == "cos") {
                stack_.push(cos(c));
            }

            if (token.value == "tan") {
                stack_.push((sin(c) / cos(c)));
            }

            if (token.value == "cot") {
                stack_.push((cos(c) / sin(c)));
            }

            if (token.value == "ln") {
                stack_.push((log(c)));
            }
        }
        rpn_tokens.pop();
    }
    result = stack_.top();
    return result;
}

double evaluate(string& expression,double x) {
    vector <Token> tokens = parse(expression);
    vector <Token> tokens_ = parseNegativeNumbers(tokens);
    queue <Token> rpn_tokens = RPN(tokens_);
    return stack_calc(rpn_tokens,x);
}

#endif //MAIN_CPP_UTILITY_H
