//
// Created by User on 29.04.2022.
//

#ifndef MAIN_CPP_BUTTON_H
#define MAIN_CPP_BUTTON_H
#include "utility.h"

class Button {
public:
    Button(const string& name, Vector2f position) {  // Constructor for each button
        button.setPosition(position);
        buttonT.loadFromFile(texturesDirectory+name);
        button.setTexture(buttonT);
    }
    void setTexture(const string& name) {
        buttonT.loadFromFile(texturesDirectory+name);
        button.setTexture(buttonT);
    }

    void setScale() {
        button.setScale(0.12,0.12);
    }

    void drawButton (RenderWindow &window) {
        window.draw(button);
    }

    void setColor(Color color) {
        button.setColor(color);
    }

    FloatRect getGlobalBounds() {
        return button.getGlobalBounds();
    }
private:
    Sprite button;
    Texture buttonT;
    string texturesDirectory = "../textures/";
};

#endif //MAIN_CPP_BUTTON_H