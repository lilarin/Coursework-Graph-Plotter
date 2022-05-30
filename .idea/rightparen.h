#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include "token.h"
#include <string>

using namespace std;

class Rightparen: public Token  //child to Token class
{
public:
    Rightparen();               //zero parameter constructor
    int GetType();              //returns the type of token it is
    string Data();              //returns the data of the token in string from
    void Print();               //displays the data

    string _face;               //variable non-private
};

Rightparen::Rightparen()            //zero parameter constructor
{
    _face = ")";
}


int Rightparen::GetType()           //returns the type
{
    return 3;
}

string Rightparen::Data()           //returns the data of the Token
{
    return _face;
}

void Rightparen::Print()            //displays the data of the Token
{
    cout<<_face;
}

#endif // RIGHTPAREN_H
