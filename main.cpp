#include <SFML/Graphics.hpp>
#include "headers/textbox.h"
#include "headers/button.h"
#include "headers/shunting_yard.h"

int main() {
    // defining the variables
    string equation,cursorPosition;
    float width = 795, height = 720, renderWidth = 1280, renderHeight = 720,
            xOriginal = 0, yOriginal = 0, CenterX = (width/2), CenterY = (height/2),Scaler = 45, PanX, PanY;
    bool isRightHold = false, isGridVisible = true, isThemeBlack = true, isCursorVisible = false;

    // rendering window and apply framerate
    RenderWindow window;
    window.create(sf::VideoMode(renderWidth,renderHeight), "Graph plotter", Style::Close);
    window.setFramerateLimit(60);

    // creating buttons using class "Button"
    Button button1("powX.png",{(renderWidth-468),70});
    Button button2("leftBracket.png",{(renderWidth-355),70});
    Button button3("rightBracket.png",{(renderWidth-241),70});
    Button button4("clean.png",{(renderWidth-127),70});
    Button button5("sin.png",{(renderWidth-468),125});
    Button button6("x.png",{(renderWidth-355),125});
    Button button7("pi.png",{(renderWidth-241),125});
    Button button8("cleanLastChar.png",{(renderWidth-127),125});
    Button button9("cos.png",{(renderWidth-468),180});
    Button button10("tan.png",{(renderWidth-355),180});
    Button button11("cot.png",{(renderWidth-241),180});
    Button button12("exp.png",{(renderWidth-127),180});
    Button button13("division.png",{(renderWidth-468),235});
    Button button14("num7.png",{(renderWidth-355),235});
    Button button15("num8.png",{(renderWidth-241),235});
    Button button16("num9.png",{(renderWidth-127),235});
    Button button17("multiplication.png",{(renderWidth-468),290});
    Button button18("num4.png",{(renderWidth-355),290});
    Button button19("num5.png",{(renderWidth-241),290});
    Button button20("num6.png",{(renderWidth-127),290});
    Button button21("minus.png",{(renderWidth-468),345});
    Button button22("num1.png",{(renderWidth-355),345});
    Button button23("num2.png",{(renderWidth-241),345});
    Button button24("num3.png",{(renderWidth-127),345});
    Button button25("plus.png",{(renderWidth-468),400});
    Button button26("num0.png",{(renderWidth-355),400});
    Button button27("dot.png",{(renderWidth-241),400});
    Button button28("result.png",{(renderWidth-127),400});
    Button button29("check.png",{width+50,height-225});
    Button button30("check.png",{width+50,height-150});
    Button button31("cross.png",{width+50,height-75});

    // defining font and text
    Font font;
    font.loadFromFile("../fonts/arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(24);

    // creating objects that will be used for tasks
    RectangleShape bounds(Vector2f(renderWidth-width, renderHeight));
    bounds.setPosition({width,0});

    CircleShape Cursor;
    Cursor.setRadius(4);

    RectangleShape CursorIntersection(Vector2f(1.f, 2*height));
    CursorIntersection.setFillColor(Color(255,255,255));

    Textbox textbox(26,Color::Black);
    textbox.setFont(font);
    textbox.setPosition({(renderWidth-458),30});

    RectangleShape inputField(Vector2f(456.f, 50.f));
    inputField.setPosition({(renderWidth-468),20});
    inputField.setFillColor(Color(255,255,255));

    // creating a vertex array to store the coordinates of points
    VertexArray Graph(LinesStrip, 2);

    // main cycle, while application is open
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case Event::Closed:    // check for window status
                    window.close();
                    break;
                case Event::MouseWheelMoved:    // check for mouse scrolling
                    if (event.mouseWheel.delta < 0 && Scaler > 6) {
                        Scaler -= Scaler * 0.1;
                    }
                    if (event.mouseWheel.delta > 0 && Scaler < 300) {
                        Scaler += Scaler * 0.1;
                    }
                    break;
                case::Event::KeyPressed:    // check for keyboard status
                    if (event.key.code == Keyboard::Enter) {
                        equation = textbox.getText();
                    }
                    if (event.key.code == Keyboard::Escape) {
                        Scaler = 45;
                        CenterX = width/2;
                        CenterY = height/2;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        if(Scaler == -1 && event.mouseWheel.delta >=1)
                            Scaler = 1;
                        Scaler+=Scaler*0.1f;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        if(Scaler == 1 && event.mouseWheel.delta <=-1)
                            Scaler = -1;
                        Scaler-=Scaler*0.1f;
                    }
                case Event::MouseButtonPressed:    // check for mouse buttons status
                    if (event.mouseButton.button == Mouse::Right) {
                        xOriginal = event.mouseButton.x;
                        yOriginal = event.mouseButton.y;
                        isRightHold = true;
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2i mousePos = Mouse::getPosition( window );
                        Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                        if ( button1.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("^");
                        }
                        if ( button2.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("(");
                        }
                        if ( button3.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu(")");
                        }
                        if ( button4.getGlobalBounds().contains( mousePosF )) {
                            textbox.deleteString();
                        }
                        if ( button5.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("sin");
                        }
                        if ( button6.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("x");
                        }
                        if ( button7.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("pi");
                        }
                        if ( button8.getGlobalBounds().contains( mousePosF )) {
                            textbox.deleteChar();
                        }
                        if ( button9.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("cos");
                        }
                        if ( button10.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("tan");
                        }
                        if ( button11.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("cot");
                        }
                        if ( button12.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("e");
                        }
                        if ( button13.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("/");
                        }
                        if ( button14.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("7");
                        }
                        if ( button15.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("8");
                        }
                        if ( button16.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("9");
                        }
                        if ( button17.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("*");
                        }
                        if ( button18.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("4");
                        }
                        if ( button19.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("5");
                        }
                        if ( button20.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("6");
                        }
                        if ( button21.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("-");
                        }
                        if ( button22.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("1");
                        }
                        if ( button23.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("2");
                        }
                        if ( button24.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("3");
                        }
                        if ( button25.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("+");
                        }
                        if ( button26.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu("0");
                        }
                        if ( button27.getGlobalBounds().contains( mousePosF )) {
                            textbox.typedButtonMenu(".");
                        }
                        if ( button28.getGlobalBounds().contains( mousePosF )) {
                            equation = textbox.getText();
                        }

                        if ( button29.getGlobalBounds().contains( mousePosF )) {
                            if (isThemeBlack) {
                                button29.setTexture("cross.png");
                                isThemeBlack = false;
                            }
                            else {
                                button29.setTexture("check.png");
                                isThemeBlack = true;
                            }
                        }
                        if ( button30.getGlobalBounds().contains( mousePosF )) {
                            if (isGridVisible) {
                                button30.setTexture("cross.png");
                                isGridVisible = false;
                            }
                            else {
                                button30.setTexture("check.png");
                                isGridVisible = true;
                            }
                        }
                        if ( button31.getGlobalBounds().contains( mousePosF )) {
                            if (isCursorVisible) {
                                button31.setTexture("cross.png");
                                isCursorVisible = false;
                            }
                            else {
                                button31.setTexture("check.png");
                                isCursorVisible = true;
                            }
                        }
                    }
                    break;
                    {case Event::MouseMoved:    // check for mouse position

                            if(isRightHold) {
                                PanX = event.mouseMove.x - xOriginal;
                                PanY = event.mouseMove.y - yOriginal;
                                CenterX+=PanX;
                                CenterY+=PanY;
                                xOriginal = event.mouseMove.x;
                                yOriginal = event.mouseMove.y;
                            }
                        Vector2i mousePos = Mouse::getPosition( window );
                        Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                        Vector2f CursorIntersectionPos( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y - height) );
                        CursorIntersection.setPosition(CursorIntersectionPos);

                        if ( button1.getGlobalBounds().contains( mousePosF )) {
                            button1.setColor( sf::Color( 183, 183, 185 ) );
                        } else button1.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button2.getGlobalBounds().contains( mousePosF )) {
                            button2.setColor( sf::Color( 183, 183, 185 ) );
                        } else button2.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button3.getGlobalBounds().contains( mousePosF )) {
                            button3.setColor( sf::Color( 183, 183, 185 ) );
                        } else button3.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button4.getGlobalBounds().contains( mousePosF )) {
                            button4.setColor( sf::Color( 248, 125, 125 ) );
                        } else button4.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button5.getGlobalBounds().contains( mousePosF )) {
                            button5.setColor( sf::Color( 183, 183, 185 ) );
                        } else button5.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button6.getGlobalBounds().contains( mousePosF )) {
                            button6.setColor( sf::Color( 183, 183, 185 ) );
                        } else button6.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button7.getGlobalBounds().contains( mousePosF )) {
                            button7.setColor( sf::Color( 183, 183, 185 ) );
                        } else button7.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button8.getGlobalBounds().contains( mousePosF )) {
                            button8.setColor( sf::Color( 248, 125, 125 ) );
                        } else button8.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button9.getGlobalBounds().contains( mousePosF )) {
                            button9.setColor( sf::Color( 183, 183, 185 ) );
                        } else button9.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button10.getGlobalBounds().contains( mousePosF )) {
                            button10.setColor( sf::Color( 183, 183, 185 ) );
                        } else button10.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button11.getGlobalBounds().contains( mousePosF )) {
                            button11.setColor( sf::Color( 183, 183, 185 ) );
                        } else button11.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button12.getGlobalBounds().contains( mousePosF )) {
                            button12.setColor( sf::Color( 183, 183, 185 ) );
                        } else button12.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button13.getGlobalBounds().contains( mousePosF )) {
                            button13.setColor( sf::Color( 183, 183, 185 ) );
                        } else button13.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button14.getGlobalBounds().contains( mousePosF )) {
                            button14.setColor( sf::Color( 183, 183, 185 ) );
                        } else button14.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button15.getGlobalBounds().contains( mousePosF )) {
                            button15.setColor( sf::Color( 183, 183, 185 ) );
                        } else button15.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button16.getGlobalBounds().contains( mousePosF )) {
                            button16.setColor( sf::Color( 183, 183, 185 ) );
                        } else button16.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button17.getGlobalBounds().contains( mousePosF )) {
                            button17.setColor( sf::Color( 183, 183, 185 ) );
                        } else button17.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button18.getGlobalBounds().contains( mousePosF )) {
                            button18.setColor( sf::Color( 183, 183, 185 ) );
                        } else button18.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button19.getGlobalBounds().contains( mousePosF )) {
                            button19.setColor( sf::Color( 183, 183, 185 ) );
                        } else button19.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button20.getGlobalBounds().contains( mousePosF )) {
                            button20.setColor( sf::Color( 183, 183, 185 ) );
                        } else button20.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button21.getGlobalBounds().contains( mousePosF )) {
                            button21.setColor( sf::Color( 183, 183, 185 ) );
                        } else button21.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button22.getGlobalBounds().contains( mousePosF )) {
                            button22.setColor( sf::Color( 183, 183, 185 ) );
                        } else button22.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button23.getGlobalBounds().contains( mousePosF )) {
                            button23.setColor( sf::Color( 183, 183, 185 ) );
                        } else button23.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button24.getGlobalBounds().contains( mousePosF )) {
                            button24.setColor( sf::Color( 183, 183, 185 ) );
                        } else button24.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button25.getGlobalBounds().contains( mousePosF )) {
                            button25.setColor( sf::Color( 183, 183, 185 ) );
                        } else button25.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button26.getGlobalBounds().contains( mousePosF )) {
                            button26.setColor( sf::Color( 183, 183, 185 ) );
                        } else button26.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button27.getGlobalBounds().contains( mousePosF )) {
                            button27.setColor( sf::Color( 183, 183, 185 ) );
                        } else button27.setColor( sf::Color( 255, 255, 255 ) );
                        if ( button28.getGlobalBounds().contains( mousePosF )) {
                            button28.setColor( sf::Color( 64, 127, 246 ) );
                        } else button28.setColor( sf::Color( 255, 255, 255 ) );
                        break;}
                case Event::MouseButtonReleased:    // check if mouse released (right click)
                    if (event.mouseButton.button == Mouse::Right) isRightHold = false;
                    break;
                case Event::TextEntered:// watching for the keyboard input
                    textbox.typedButtonKeyboard(event);
            }
        }

        // checks bool value and apply colors for background after clearing it
        if (!isThemeBlack) window.clear(Color(240,240,240));
        else window.clear(Color::Black);

        // creates additional scaler for scaling numbers and lines on the
        float FScaler = Scaler;
        while ( width / FScaler > 20) {
            FScaler *= 2;
        }


        VertexArray Line(LinesStrip, 2);

        // checks bool value and apply colors for lines of the grid
        if (isThemeBlack) {
            Line[0].color = {215, 215, 215};
            Line[1].color = {215, 215, 215};
            text.setFillColor({215, 215, 215});
        }
        else {
            Line[0].color = {60, 60, 60};
            Line[1].color = {60, 60, 60};
            text.setFillColor({40, 40, 40});
        }

        // creates x and y axis
        Line[0].position = Vector2f(CenterX, (0));
        Line[1].position = Vector2f(CenterX, (height));
        window.draw(Line);
        Line[0].position = Vector2f((0), CenterY);
        Line[1].position = Vector2f((width), CenterY);
        window.draw(Line);

        // creates the dimension (numbers) on the axes
        for(float i = 0; i<=width/2+(-1*(CenterX-width/2)); i+=FScaler)
        {
            text.setString(intToString(i/Scaler));
            text.setPosition((i+CenterX),CenterY);
            window.draw(text);
        }
        for(float i = 0; i>=-width/2+(-1*(CenterX-width/2)); i-=FScaler)
        {
            text.setString(intToString(i/Scaler));
            text.setPosition((i+CenterX),CenterY);
            if (i != 0) {
                window.draw(text);
            }
        }
        for(float i = 0; i<=height/2+(CenterY-height/2); i+=FScaler)
        {
            text.setString(intToString(i/Scaler));
            text.setPosition(CenterX,CenterY-i);
            if (i != 0) {
                window.draw(text);
            }
        }
        for(float i = 0; i>=-height/2+(CenterY-height/2); i-=FScaler)
        {
            text.setString(intToString(i/Scaler));
            text.setPosition(CenterX,CenterY-i);
            if (i != 0) {
                window.draw(text);
            }
        }

        // create lines on the axes
        for(float i = 0; i <= width/2+(CenterX-width/2); i+=FScaler)
        {
            Line[0].position = Vector2f(CenterX-i, CenterY-(10));
            Line[1].position = Vector2f(CenterX-i, CenterY+(10));
            window.draw(Line);
        }
        for(float i = 0; i <= width/2+(-1*(CenterX-width/2)); i+=FScaler)
        {
            Line[0].position = Vector2f(CenterX+i, CenterY-(10));
            Line[1].position = Vector2f(CenterX+i, CenterY+(10));
            window.draw(Line);
        }
        for(float i = 0; i <= height/2+(-1*(CenterY-height/2)); i+=FScaler)
        {
            Line[0].position = Vector2f(CenterX-(10),CenterY+i);
            Line[1].position = Vector2f(CenterX+(10),CenterY+i);
            window.draw(Line);
        }
        for(float i = 0; i <= height/2+((CenterY-height/2)); i+=FScaler)
        {
            Line[0].position = Vector2f(CenterX-(10),CenterY-i);
            Line[1].position = Vector2f(CenterX+(10),CenterY-i);
            window.draw(Line);
        }

        if (isGridVisible) {
            // checks bool value and apply colors for lines of the grid
            if (isThemeBlack) {
                Line[0].color = {50, 50, 50};
                Line[1].color = {50, 50, 50};
            }
            else {
                Line[0].color = {200, 200, 200};
                Line[1].color = {200, 200, 200};
            };

            // creates the horizontal and vertical lines of the grid
            for(float i = 1; i <= width/2+(CenterX-width/2); i+=FScaler)
            {
                Line[0].position = Vector2f(CenterX-i, 0);
                Line[1].position = Vector2f(CenterX-i, height);
                window.draw(Line);
            }
            for(float i = 1; i <= width/2+(-1*(CenterX-width/2)); i+=FScaler)
            {
                Line[0].position = Vector2f(CenterX+i, 0);
                Line[1].position = Vector2f(CenterX+i, height);
                window.draw(Line);
            }
            for(float i = 1; i <= height/2+(-1*(CenterY-height/2)); i+=FScaler)
            {
                Line[0].position = Vector2f(0,CenterY+i);
                Line[1].position = Vector2f(width,CenterY+i);
                window.draw(Line);
            }
            for(float i = 1; i <= height/2+((CenterY-height/2)); i+=FScaler)
            {
                Line[0].position = Vector2f(0,CenterY-i);
                Line[1].position = Vector2f(width,CenterY-i);
                window.draw(Line);
            }
        }

        // checks bool value and apply colors for graph and dot with coordinates (x,y)
        if (isThemeBlack) {
            Graph[0].color = {75, 251, 75};
            Graph[1].color = {75, 251, 75};
            Cursor.setFillColor({75, 251, 75});
            text.setFillColor({255, 255, 255});
        }
        else {
            Graph[0].color = Color::Red;
            Graph[1].color = Color::Red;
            Cursor.setFillColor(Color::Red);
            text.setFillColor({0, 0, 0});
        }

        float lastPositive = (width/2+(-1*(CenterX-width/2)))/Scaler,
                lastNegative = (-width/2+(-1*(CenterX-width/2)))/Scaler;

        // if equation is not empty - continue
        if (!equation.empty()) {
            for(float x = lastNegative; x < lastPositive; x += 1/Scaler) // 1/Scaler is responsible for the number of lines per unit
            {
                // Creating points that will be connected in each cycle step and draw them
                Graph[0].position = Vector2f((x*Scaler+CenterX),(evaluate(equation,x)*Scaler*-1+CenterY));
                Graph[1].position = Vector2f(((x+1/Scaler)*Scaler+CenterX),(evaluate(equation,x+1/Scaler)*Scaler*-1+CenterY));
                if (fabs(Graph[1].position.y) < 1000) {
                    window.draw(Graph);
                }

                // checks bool value of drawing coordinates on the plot based on mouse position
                if (isCursorVisible) {
                    if ( CursorIntersection.getGlobalBounds().contains(Graph[0].position) ) {
                        Vector2i mousePos = Mouse::getPosition( window );
                        Vector2f textPos( static_cast<float>( mousePos.x + 20 ), static_cast<float>( (Graph[0].position.y) ) );
                        Vector2f cursorPos( static_cast<float>( mousePos.x - 3 ), static_cast<float>( (Graph[0].position.y) - 3) );

                        text.setPosition(textPos);
                        Cursor.setPosition(cursorPos);

                        cursorPosition = "( ";
                        cursorPosition += intToString(roundValue((mousePos.x-width/2+(-1*(CenterX-width/2)))/Scaler));
                        cursorPosition += " , ";
                        cursorPosition += intToString(roundValue((-(Graph[0].position.y)+height/2-(-1*(CenterY-height/2)))/Scaler));
                        cursorPosition += " )";

                        text.setString(cursorPosition);
                        window.draw(text);
                        window.draw(Cursor);

                    }
                }
            }
        }

        // Checks bool and apply color for menu field background
        if (isThemeBlack) bounds.setFillColor(Color::Black);
        else bounds.setFillColor(Color(240,240,240));

        // draw bounds for menu, input field for users input and background field for it
        window.draw(bounds);
        window.draw(inputField);
        textbox.drawTo(window);

        // draw text for menu
        text.setString("Dark theme");
        text.setPosition({width+100,height-225});
        window.draw(text);
        text.setString("Grid on the plane");
        text.setPosition({width+100,height-150});
        window.draw(text);
        text.setString("Cursor on the plane");
        text.setPosition({width+100,height-75});
        window.draw(text);

        // Draw all buttons using class
        button1.drawButton(window);
        button2.drawButton(window);
        button3.drawButton(window);
        button4.drawButton(window);
        button5.drawButton(window);
        button6.drawButton(window);
        button7.drawButton(window);
        button8.drawButton(window);
        button9.drawButton(window);
        button10.drawButton(window);
        button11.drawButton(window);
        button12.drawButton(window);
        button13.drawButton(window);
        button14.drawButton(window);
        button15.drawButton(window);
        button16.drawButton(window);
        button17.drawButton(window);
        button18.drawButton(window);
        button19.drawButton(window);
        button20.drawButton(window);
        button21.drawButton(window);
        button22.drawButton(window);
        button23.drawButton(window);
        button24.drawButton(window);
        button25.drawButton(window);
        button26.drawButton(window);
        button27.drawButton(window);
        button28.drawButton(window);
        button29.setScale();
        button30.setScale();
        button31.setScale();
        button29.drawButton(window);
        button30.drawButton(window);
        button31.drawButton(window);


        // displays everything drawn
        window.display();

    }
}