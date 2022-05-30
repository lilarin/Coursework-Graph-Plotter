#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;

class Token                 //parents class to other classes
{
public:
    Token();                //zero parameter constructor
    virtual int GetType();  //returns the type

    virtual void Print();   //displays
    virtual string Data();  //returns data from the token
};

Token::Token()          //zero parameter constructor
{
}

int Token::GetType()    //returns the type of the Token
{
    return 0;
}


void Token::Print()     //does nothing here, is a virtual function
{
}

string Token::Data()    //does nothing important here, vitrual
{
    return "!";
}


#endif // TOKEN_H
