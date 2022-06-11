//
// Created by User on 29.04.2022.
//

#ifndef MAIN_CPP_TEXTBOX_H
#define MAIN_CPP_TEXTBOX_H
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;

// class with user input processing and correct operation of the input field
class Textbox {
public:
    Textbox(int size, Color color) { // Constructor for input field
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        textbox.setString("_");
    }

    void setFont(Font &font) { // function for defining font of text field
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos) { // function for draw input field
        textbox.setPosition(pos);
    }

    string getText() {  // function for get text
        return text.str();
    }

    void drawTo (RenderWindow &window) { // function for draw input field
        window.draw(textbox);
    }

    void typedButtonKeyboard(Event input) {
        int charTyped = input.text.unicode; // Converting text for check is it from latin alphabet
        if (charTyped < 128) {
            if (text.str().length() <= limit) {
                inputLogic(charTyped);
            }
            else if(text.str().length() > limit && charTyped && DELETE_KEY) {
                deleteLastChar();
            }
        }
    }

    void typedButtonMenu(const string& inputButton) {
        int i = 0;
        while (i<inputButton.length()) {
            if (text.str().length() <= limit) {
                inputLogic(inputButton[i]);
            }
            else if(text.str().length() > limit && inputButton[i] && DELETE_KEY) {
                deleteLastChar();
            }
            i++;
        }
    }

    void deleteChar() {
        if (text.str().length() != 0) {
            deleteLastChar();
        }
        textbox.setString(text.str() + "_");
    }

    void deleteString() {
        if (text.str().length() != 0) {
            while (text.str().length() > 0) {
                deleteLastChar();
            }
            textbox.setString("_");
        }
    }

private:
    Text textbox;
    ostringstream text;
    int limit = 30;

    void inputLogic(int charTyped) {
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() {
        string str = text.str();
        string newStr;
        for (int i = 0; i < str.length()-1; i++) {
            newStr += str[i];
        }
        text.str("");
        text << newStr;
    }
};

#endif //MAIN_CPP_TEXTBOX_H
