//
// Created by User on 29.04.2022.
//

#ifndef MAIN_CPP_BUTTON_H
#define MAIN_CPP_BUTTON_H
#include <unistd.h>

class Button {
public:

    Button(string path, Vector2f position) {
        button.setPosition(position);
        char temp[100];
        string tempString = getcwd(temp, 256);
        replace(projectDirectory.begin(), projectDirectory.end(), '\\', '/');
        for (int i = 0; i < tempString.length()-18; i++) {
            projectDirectory += tempString[i];
        }
        buttonT.loadFromFile(projectDirectory+path);
        button.setTexture(buttonT);
    }
    void setTexture(string path) {
        buttonT.loadFromFile(projectDirectory+path);
        button.setTexture(buttonT);
    }

    void scale() {
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
    string projectDirectory;
};

#endif //MAIN_CPP_BUTTON_H
