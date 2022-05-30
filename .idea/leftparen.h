#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include "token.h"
#include <string>

using namespace std;

class Leftparen: public Token   //child class of Token
{
public:
    Leftparen();                //constructor
    int GetType();              //gets the type of Token
    string Data();              //returns the data in the Token
    void Print();               //displays the Token data

    string face;               //variable, non-private

};

Leftparen::Leftparen()              //zero parameter constructor
{
    face = "(";
}


int Leftparen::GetType()            //gets the type
{
    return 2;
}

string Leftparen::Data()            //gets the data from the token
{
    return face;
}

void Leftparen::Print()             //displays the data of the token
{
    cout<<face;
}


#endif // LEFTPAREN_H
