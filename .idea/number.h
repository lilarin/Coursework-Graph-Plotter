#ifndef NUMBER_H
#define NUMBER_H
#include "token.h"
#include <string>

using namespace std;

class Number: public Token  //child class of Token
{
public:
    Number();               //zero constructor
    Number(string input);   //single variable constructor
    int GetType();          //returns the type of var
    void Print();           //displays the data
    string Data();          //returns the data

    string num;             //variable non-private


};

Number::Number()                //zero parameter constructor
{
}

Number::Number(string input)    //single parameter constructor
{
    num = input;
}

int Number::GetType()           //returns the type
{
    return 0;
}

void Number::Print()            //displays the data of the token
{
    cout<<num;
}

string Number::Data()           //returns the data of the Token
{
    return num;
}


#endif // NUMBER_H
