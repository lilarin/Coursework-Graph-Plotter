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


class Textbox {
public:
    Textbox(int size, Color color, bool sel) {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = sel;
        if (sel) {
            textbox.setString("_");
        }
        else {
            textbox.setString("");
        }
    }

    void setFont(Font &font) {
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos) {
        textbox.setPosition(pos);
    }

    string getText() {
        return text.str();
    }

    void drawTo (RenderWindow &window) {
        window.draw(textbox);
    }

    void typedOn(Event input) {
        if (isSelected) {
            int charTyped = input.text.unicode;
            if (charTyped < 128) {
                if (hasLimit) {
                    if (text.str().length() <= limit) {
                        inputLogic(charTyped);
                    }
                    else if(text.str().length() > limit && charTyped && DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                else {
                    inputLogic(charTyped);
                }
            }
        }
    }
    void typedButton(const string& inputButton) {
        string charTyped = inputButton;
        for (int i=0; i<inputButton.length(); i++) {
            if (charTyped[i] < 128) {
                if (hasLimit) {
                    if (text.str().length() <= limit) {
                        inputLogic(charTyped[i]);
                    }
                    else if(text.str().length() > limit && charTyped[i] && DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                else {
                    inputLogic(charTyped[i]);
                }
            }
        }
    }

    void deleteChar() {
        if (text.str().length() != 0) {
            deleteLastChar();
        }
        textbox.setString(text.str() + "_");
    }
    void deleteString() {
        while (text.str().length() > 0) {
            deleteLastChar();
        }
        textbox.setString("_");
    }
private:
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool hasLimit = true;
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
