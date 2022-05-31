#include <SFML/Graphics.hpp>
#include "textbox.h"
#include <string>
#include "button.h"
#include "shunting_yard.h"

string intToString(double number) {
    stringstream ss;             //create a stringstream
    string str;
    ss << number;                //add number to the stream
    ss >> str;                   //push the contents onto a string
    return str;                  //return the string
}


int main()
{
//    string equation = "0.5^x-(x+(-2))^2+1";
    string equation = "10^6";

    float width = 795, height = 720, renderWidth = 1280, renderHeight = 720, xOriginal = 0, yOriginal = 0,
    CenterX = (width/2), CenterY = (height/2);
    double Scaler = 10, PanX, PanY;


    bool hold = false, isGridVisible = true, isThemeBlack = true;


    RenderWindow window;
    if (!window.isOpen()) {
        window.create(sf::VideoMode(renderWidth,renderHeight), "Graph plotter", Style::Close);
    }

    window.setFramerateLimit(60);


    ContextSettings settings;
    settings.antialiasingLevel = 8;


    Button button1("/textures/powX.png",{(renderWidth-468),70});
    Button button2("/textures/leftBracket.png",{(renderWidth-355),70});
    Button button3("/textures/rightBracket.png",{(renderWidth-241),70});
    Button button4("/textures/clean.png",{(renderWidth-127),70});
    Button button5("/textures/sin.png",{(renderWidth-468),125});
    Button button6("/textures/x.png",{(renderWidth-355),125});
    Button button7("/textures/pi.png",{(renderWidth-241),125});
    Button button8("/textures/cleanLastChar.png",{(renderWidth-127),125});
    Button button9("/textures/cos.png",{(renderWidth-468),180});
    Button button10("/textures/tan.png",{(renderWidth-355),180});
    Button button11("/textures/cot.png",{(renderWidth-241),180});
    Button button12("/textures/exp.png",{(renderWidth-127),180});
    Button button13("/textures/division.png",{(renderWidth-468),235});
    Button button14("/textures/num7.png",{(renderWidth-355),235});
    Button button15("/textures/num8.png",{(renderWidth-241),235});
    Button button16("/textures/num9.png",{(renderWidth-127),235});
    Button button17("/textures/multiplication.png",{(renderWidth-468),290});
    Button button18("/textures/num4.png",{(renderWidth-355),290});
    Button button19("/textures/num5.png",{(renderWidth-241),290});
    Button button20("/textures/num6.png",{(renderWidth-127),290});
    Button button21("/textures/minus.png",{(renderWidth-468),345});
    Button button22("/textures/num1.png",{(renderWidth-355),345});
    Button button23("/textures/num2.png",{(renderWidth-241),345});
    Button button24("/textures/num3.png",{(renderWidth-127),345});
    Button button25("/textures/plus.png",{(renderWidth-468),400});
    Button button26("/textures/num0.png",{(renderWidth-355),400});
    Button button27("/textures/dot.png",{(renderWidth-241),400});
    Button button28("/textures/result.png",{(renderWidth-127),400});

    Button button29("/textures/check.png",{width+50,height-200});
    Button button30("/textures/check.png",{width+50,height-100});

//    Button info("/textures/info.png",{(renderWidth-473),465});

    RectangleShape bounds(Vector2f(renderWidth-width, renderHeight));
    bounds.setPosition({width,0});


    Font font;
    font.loadFromFile("C:/arial.ttf");
    Textbox textbox1(26,Color::Black, true);
    textbox1.setFont(font);
    textbox1.setPosition({(renderWidth-458),30});

    RectangleShape inputField(Vector2f(456.f, 50.f));
    inputField.setPosition({(renderWidth-468),20});
    inputField.setFillColor(Color(255,255,255));


    Text text;
    text.setFont(font);
    text.setCharacterSize(24);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
//                case Event::MouseLeft:
//                    button1.setColor(sf::Color(255, 255, 255));
//                    button2.setColor(sf::Color(255, 255, 255));
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseWheelMoved:            //will check for mouse scrolling
                    if(Scaler == 1 && event.mouseWheel.delta <=-1)      //will not allow Scaler to become 0
                        Scaler = -1;
                    else if(Scaler == -1 && event.mouseWheel.delta >=1) //will not allow Scaler to become 0
                        Scaler = 1;
                    if(event.mouseWheel.delta<0)
                        Scaler-=Scaler*0.1;
                    if(event.mouseWheel.delta>0)
                        Scaler+=Scaler*0.1;
                    break;
                case::Event::KeyPressed:
                    if (event.key.code == Keyboard::Enter) {
                        string temp = textbox1.getText();
                        if (temp.length()!=0) {
                            equation = temp;
                        }
                    }
                    if (event.key.code == Keyboard::Escape) {
                        Scaler = 10;
                        CenterX = width/2;
                        CenterY = height/2;
                    }
                    if (event.key.code == Keyboard::Z) {
                        if (isThemeBlack) isThemeBlack = false;
                        else isThemeBlack = true;
                    }
                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Right) {
                        xOriginal = event.mouseButton.x;
                        yOriginal = event.mouseButton.y;
                        hold = true;
                    }
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2i mousePos = Mouse::getPosition( window );
                        Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                        if ( button1.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("^");
                        }
                        if ( button2.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("(");
                        }
                        if ( button3.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton(")");
                        }
                        if ( button4.getGlobalBounds().contains( mousePosF )) {
                            textbox1.deleteString();
                        }
                        if ( button5.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("sin");
                        }
                        if ( button6.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("x");
                        }
                        if ( button7.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("pi");
                        }
                        if ( button8.getGlobalBounds().contains( mousePosF )) {
                            textbox1.deleteChar();
                        }
                        if ( button9.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("cos");
                        }
                        if ( button10.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("tan");
                        }
                        if ( button11.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("cot");
                        }
                        if ( button12.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("e");
                        }
                        if ( button13.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("/");
                        }
                        if ( button14.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("7");
                        }
                        if ( button15.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("8");
                        }
                        if ( button16.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("9");
                        }
                        if ( button17.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("*");
                        }
                        if ( button18.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("4");
                        }
                        if ( button19.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("5");
                        }
                        if ( button20.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("6");
                        }
                        if ( button21.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("-");
                        }
                        if ( button22.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("1");
                        }
                        if ( button23.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("2");
                        }
                        if ( button24.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("3");
                        }
                        if ( button25.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("+");
                        }
                        if ( button26.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton("0");
                        }
                        if ( button27.getGlobalBounds().contains( mousePosF )) {
                            textbox1.typedButton(".");
                        }
                        if ( button28.getGlobalBounds().contains( mousePosF )) {
                            string temp = textbox1.getText();
                            if (temp.length()!=0) {
                                equation = temp;
                            }
                        }


                        if ( button29.getGlobalBounds().contains( mousePosF )) {
                            if (isThemeBlack) {
                                button29.setTexture("/textures/cross.png");
                                isThemeBlack = false;
                            }
                            else {
                                button29.setTexture("/textures/check.png");
                                isThemeBlack = true;
                            }
                        }

                        if ( button30.getGlobalBounds().contains( mousePosF )) {
                            if (isGridVisible) {
                                button30.setTexture("/textures/cross.png");
                                isGridVisible = false;
                            }
                            else {
                                button30.setTexture("/textures/check.png");
                                isGridVisible = true;
                            }
                        }
                    }
                    break;
                    {case Event::MouseMoved:
                        if(hold) {
                            PanX = event.mouseMove.x - xOriginal;
                            PanY = event.mouseMove.y - yOriginal;
                            CenterX+=PanX;
                            CenterY+=PanY;
                            xOriginal = event.mouseMove.x;
                            yOriginal = event.mouseMove.y;
                        }
                        Vector2i mousePos = Mouse::getPosition( window );
                        Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

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
                case Event::MouseButtonReleased:
                    if (event.mouseButton.button == Mouse::Right) hold = false;
                    break;
                case Event::TextEntered:
                    textbox1.typedOn(event);
            }
        }

        if (!isThemeBlack) window.clear(Color(240,240,240));
        else window.clear(Color::Black);

        font.loadFromFile("C:/arial.ttf");
        Text dimension;
        dimension.setFont(font);
        dimension.setColor(sf::Color::White);

        double FScaler = Scaler;
        while(width/FScaler > 20) {
            FScaler *= 2;
        }


        VertexArray Line(LinesStrip, 2);
        if (isThemeBlack) {
            Line[0].color = {255, 255, 255};
            Line[1].color = {255, 255, 255};
            text.setFillColor({255, 255, 255});
        }
        else {
            Line[0].color = {0, 0, 0};
            Line[1].color = {0, 0, 0};
            text.setFillColor({0, 0, 0});
        }
        Line[0].position = Vector2f(CenterX, (0));                    //creates the y axis
        Line[1].position = Vector2f(CenterX, (height));                 // ''
        window.draw(Line);                                             //draws the y axis
        Line[0].position = Vector2f((0), CenterY);                    //creates the x axis
        Line[1].position = Vector2f((width), CenterY);                 //''
        window.draw(Line);


        double lastPositive = (width/2+(-1*(CenterX-width/2)))/Scaler,lastNegative = (-width/2+(-1*(CenterX-width/2)))/Scaler;
        for(double i = 0; i<=width/2+(-1*(CenterX-width/2)); i+=FScaler)    //creates the Positive X numbers on the grid
        {
            text.setString(intToString(i/Scaler));
            text.setPosition((i+CenterX),CenterY);
            window.draw(text);
        }
        for(double i = 0; i>=-width/2+(-1*(CenterX-width/2)); i-=FScaler)     //creates the Negative X numbers on the grid
        {
            text.setString(intToString(i/Scaler));
            text.setPosition((i+CenterX),CenterY);
            window.draw(text);
        }
        for(double i = 0; i<=height/2+(CenterY-height/2); i+=FScaler)           //creates the Positive Y numbers on the grid
        {
            text.setString(intToString(i/Scaler));
            text.setPosition(CenterX,CenterY-i);
            window.draw(text);
        }
        for(double i = 0; i>=-height/2+(CenterY-height/2); i-=FScaler)          //creates the Negative Y numbers on the grid
        {
            text.setString(intToString(i/Scaler));
            text.setPosition(CenterX,CenterY-i);
            window.draw(text);
        }

        for(double i = 0; i <= width/2+(CenterX-width/2); i+=FScaler)                          //creates the lines by the numbers Negative X grid
        {
            Line[0].position = Vector2f(CenterX-i, CenterY-(10));
            Line[1].position = Vector2f(CenterX-i, CenterY+(10));
            window.draw(Line);
        }
        for(double i = 0; i <= width/2+(-1*(CenterX-width/2)); i+=FScaler)                          //creates the lines by the numbers Positive X grid
        {
            Line[0].position = Vector2f(CenterX+i, CenterY-(10));
            Line[1].position = Vector2f(CenterX+i, CenterY+(10));
            window.draw(Line);
        }
        for(double i = 0; i <= height/2+(-1*(CenterY-height/2)); i+=FScaler)                          //creates the lines by the numbers
        {
            Line[0].position = Vector2f(CenterX-(10),CenterY+i);
            Line[1].position = Vector2f(CenterX+(10),CenterY+i);
            window.draw(Line);
        }
        for(double i = 0; i <= height/2+((CenterY-height/2)); i+=FScaler)                          //creates the lines by the numbers
        {
            Line[0].position = Vector2f(CenterX-(10),CenterY-i);
            Line[1].position = Vector2f(CenterX+(10),CenterY-i);
            window.draw(Line);
        }

        if (isGridVisible) {
            if (isThemeBlack) {
                Line[0].color = {50, 50, 50};
                Line[1].color = {50, 50, 50};
            }
            else {
                Line[0].color = {200, 200, 200};
                Line[1].color = {200, 200, 200};
            };
            for(double i = 1; i <= width/2+(CenterX-width/2); i+=FScaler)                          //creates the lines by the numbers Negative X grid
            {
                Line[0].position = Vector2f(CenterX-i, 0);
                Line[1].position = Vector2f(CenterX-i, height);
                window.draw(Line);
            }
            for(double i = 1; i <= width/2+(-1*(CenterX-width/2)); i+=FScaler)                          //creates the lines by the numbers Positive X grid
            {
                Line[0].position = Vector2f(CenterX+i, 0);
                Line[1].position = Vector2f(CenterX+i, height);
                window.draw(Line);
            }
            for(double i = 1; i <= height/2+(-1*(CenterY-height/2)); i+=FScaler)                          //creates the lines by the numbers
            {
                Line[0].position = Vector2f(0,CenterY+i);
                Line[1].position = Vector2f(width,CenterY+i);
                window.draw(Line);
            }
            for(double i = 1; i <= height/2+((CenterY-height/2)); i+=FScaler)                          //creates the lines by the numbers
            {
                Line[0].position = Vector2f(0,CenterY-i);
                Line[1].position = Vector2f(width,CenterY-i);
                window.draw(Line);
            }
        }

        if (isThemeBlack) {
            Line[0].color = {75, 251, 75};
            Line[1].color = {75, 251, 75};
        }
        else {
            Line[0].color = Color::Red;
            Line[1].color = Color::Red;
        }




        for(double x = lastNegative; x < lastPositive; x += 1/Scaler)                  //draws the graph in increments of 0.1
        {
            double x_ = x;
            evaluate(equation,x_);
            Line[0].position = sf::Vector2f((x*Scaler+CenterX),(evaluate(equation,x_)*Scaler*-1+CenterY));
            x_ = x+1/Scaler;
            Line[1].position = sf::Vector2f(((x+1/Scaler)*Scaler+CenterX),(evaluate(equation,x_)*Scaler*-1+CenterY));
            window.draw(Line);
        }


        if (isThemeBlack) bounds.setFillColor(Color::Black);
        else bounds.setFillColor(Color(240,240,240));
        window.draw(bounds);
        window.draw(inputField);
        textbox1.drawTo(window);

        text.setString("Dark theme");
        text.setPosition({width+100,height-200});
        window.draw(text);
        text.setString("Grid on the plane");
        text.setPosition({width+100,height-100});
        window.draw(text);

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
        button29.scale();
        button30.scale();
        button29.drawButton(window);
        button30.drawButton(window);


        window.display();
        //displays everything drawn
    }
}