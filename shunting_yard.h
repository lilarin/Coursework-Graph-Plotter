//
// Created by User on 29.04.2022.
//

#ifndef MAIN_CPP_SHUNTING_YARD_H
#define MAIN_CPP_SHUNTING_YARD_H
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>

using namespace std;

enum Token_type // Defining token types
{
    NUMBER,
    OPERATOR,
    BRACKET,
    FUNCTION,
    CONSTANT
};

struct Token // Creating struct of token, which consists of token type and value
{
    Token_type type;
    string value;
};

vector<Token> parse(const string& expression)
{
    vector <Token> tokens; // creating dynamic array with type of structure "Token"
    string digits; // creating digits
    string letters;
    int i = 0;
    while (i < expression.size()) { // while is not end of the string
        char character = expression[i];

        if (isdigit(character) || character == '.') { // for decimals
            digits.push_back(character);
        }

        else if (isalpha(character)) { // if char is a latter. for ex. a, c, d (for functions)
            letters.push_back(character); // separate array to store letters
        }

        else if ((character == '+') || (character == '-') || (character == '*') || (character == '/') || (character == '^')) {
            Token sign;

            if (!digits.empty()) { //if diigts present - push all and clear
                sign.type = Token_type::NUMBER;
                sign.value = digits;
                tokens.push_back(sign);
                digits = "";
            }

            if (!letters.empty()) { // if letters present - push all and clear
                sign.type = Token_type::CONSTANT;
                sign.value = letters;
                tokens.push_back(sign);
                letters = "";
            }

            sign.type = Token_type::OPERATOR; // if operator (e, pi)
            sign.value = character;
            tokens.push_back(sign);
        }
        else if (character == '(') {
            Token bracket;

            if (!letters.empty()) { // if open bracket, firstly push function and then push bracket
                bracket.type = Token_type::FUNCTION;  // that is for case like that cos(, sin( , etc.
                bracket.value = letters;
                tokens.push_back(bracket);
                letters = "";
            }
            // else push only bracket to the stack
            bracket.type = Token_type::BRACKET;
            bracket.value = character;
            tokens.push_back(bracket);
        }
        else if (character == ')') {
            Token sign;

            if (!digits.empty()) { // if digits present - push all and clear
                sign.type = Token_type::NUMBER;
                sign.value = digits;
                tokens.push_back(sign);
                digits = "";
            }

            if (!letters.empty()) { // if letters present - push all and clear
                sign.type = Token_type::CONSTANT;
                sign.value = letters;
                tokens.push_back(sign);
                letters = "";
            }
            // else push only bracket
            sign.type = Token_type::BRACKET;
            sign.value = character;
            tokens.push_back(sign);
        }
        i++;
    }
    // if digits still present - push all to the stack of tokens
    Token token;
    if (!digits.empty()) {
        token.type = Token_type::NUMBER;
        token.value = digits;
        tokens.push_back(token);
    }
    // if letters still present - push all to the stack of tokens
    if (!letters.empty()) {
        token.type = Token_type::CONSTANT;
        token.value = letters;
        tokens.push_back(token);
    }
    // return stack with tokens (they are still locking familiar to 1+cos(x), not like rpn
    return tokens;
}

vector<Token> parseNegativeNumbers(vector <Token>& tokens)
{
    vector <Token> tokens_;
    int i = 0;
    while (i < tokens.size()) {
        Token symbol = tokens[i];

        if (symbol.type == Token_type::NUMBER) {
            tokens_.push_back(symbol);
        }

        if (symbol.type == Token_type::BRACKET) {
            tokens_.push_back(symbol);
        }

        if (symbol.type == Token_type::FUNCTION) {
            tokens_.push_back(symbol);
        }

        // the whole point is that if the function finds a "-" sign without values
        // in front of it (like numbers, constants, and brackets), it adds 0 before that number and subtracts it.
        else if ((symbol.type == Token_type::OPERATOR) || (symbol.type == Token_type::CONSTANT)) {
            if (((tokens_.empty()) || (tokens_.back().value == "(")) && symbol.value == "-") {
                Token token;
                token.type = Token_type::NUMBER;
                token.value = "0";

                tokens_.push_back(token);
                tokens_.push_back(symbol);
            }
            else {
                tokens_.push_back(symbol);
            }
        }
        i++;
    }
    // return stack with tokens but if in the previous step there were something like that: -x*2-(-x)
    // now it returns expression like that: 0-x*2-(0-x). so now we can finally convert this to rpn
    return tokens_;
}

int getPrecision(const Token& symbol) { // here we get precision for the operators
    if ((symbol.value == "+") || (symbol.value == "-")) return 1;
    if ((symbol.value == "*") || (symbol.value == "/")) return 2;
    if (symbol.value == "^") return 3;
    return 0;
}

queue <Token> RPN(const vector <Token>& tokens) { // main part of the Shunting-Yard
    queue <Token> output;
    stack <Token> stack_;
    int i = 0;
    while (i < tokens.size()) {
        Token symbol = tokens[i];

        if ((symbol.type == Token_type::NUMBER) || (symbol.type == Token_type::CONSTANT)) {
            output.push(symbol);
        }

        if (symbol.type == Token_type::FUNCTION) {
            stack_.push(symbol);
        }

        // this part is responsible for moving the higher-priority operators
        // on the stack and the lower-priority ones to the queue
        if (symbol.type == Token_type::OPERATOR) {
            while ((!stack_.empty()) && (stack_.top().value != "(") && ((stack_.top().type == Token_type::FUNCTION) || (getPrecision(stack_.top()) >= getPrecision(symbol))))
            {
                output.push(stack_.top());
                stack_.pop();
            }
            stack_.push(symbol);
        }

        if (symbol.value == "(") {
            stack_.push(symbol);
        }

        if (symbol.value == ")") { // while function can not find "(" it will devastate stack and fill queue
            while (stack_.top().value != "(") {
                output.push(stack_.top());
                stack_.pop();
            }
            if (stack_.top().value == "(") {
                stack_.pop();
            }
        }
        i++;
    }
    // drags all the remaining contents of the stack to the queue and clears the stack
    while(!stack_.empty()) {
        output.push(stack_.top());
        stack_.pop();
    }
    return output;
}


#endif //MAIN_CPP_SHUNTING_YARD_H