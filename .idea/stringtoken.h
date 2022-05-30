#ifndef STRINGTOKEN_H
#define STRINGTOKEN_H

#include "token.h"
#include <queue>
#include <string>
#include "number.h"
#include "operator.h"
#include "leftparen.h"
#include "rightparen.h"
#include <iostream>

using namespace std;

queue<Token*> GetToken(string input);                                   //Tokenizes an input string
int zorg(string str, string Digits, string Letters,                     //zorgs returns the type
string Characters, string Space, string LeftP, string RightP, string Comma);          //zorg
void StrCpy(string Input, string &token, int &pos, int notpos);         //copies a string into another one
int StrLen(string Input);                                               //returns the length of a string
int StrFind(string str, char key);                                      //finds a character inside a string
int Firstof(string str, string charset, int Pos);                       //finds the first character from a char set in a string
int FirstNotof( string str, string charset, int Pos);                   //finds the first character not in a char set inside a string
int CountKey(string str, char key);





queue<Token*> GetToken(string input)
{
    string D = "x0123456789.";               //initializes doubles
    string L = "cosintaeMx";                //initializes letters for trig
    string C = "+-*/^";                     //initializes operators
    string S = " ";                        //initializes spaces
    string Comma = ",";
    string LP = "(";                        //initializes left parenthasis
    string RP = ")";                        //initializes right parenthasis
    string Paren("Invalid Character!");

    int type, FNO;                          //init ints type and FNO

    queue<Token*> infix;                    //initializes queue infix of token pointer type

    while(input.size() > 0)                                         //while string input is not empty
    {

        type = zorg(input, D, L, C, S, LP, RP, Comma);                     //set type equal to what zorg returns

        switch(type)                                                //switch case for the type
        {
            case 1 : FNO = FirstNotof(input, D, 0);                 //case 1 is numbers in double format, set FNO to the output of firstnotof
                    if(FNO == -1)                                   //if this is the last number in the input
                    {
                        infix.push(new Number(input));              //push the number into the infix queue
                        input = "";                                 //change the input string to empty
                        break;                                      //break
                    }
                    if(CountKey(input.substr(0, FNO),'.') > 1)
                    {
                        string Paren("Error! Too Many '.'");
                        throw(Paren);
                    }
                    infix.push(new Number(input.substr(0, FNO)));   //else, push the substring from 0 to where the type changes
                    input = input.substr(FNO);                      //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //break

            case 2 : FNO = FirstNotof(input, L, 0);                 //checks for letters
                    if(FNO == -1)                                   //if last letter
                    {
                        infix.push(new Operator(input));            //push the letter into the infix queue
                        input = "";                                 //change the input string to empty
                        break;                                      //break
                    }
                    infix.push(new Operator(input.substr(0, FNO))); //else, push the substring from 0 to where the type changes
                    input = input.substr(FNO);                      //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //break

            case 3 : FNO = FirstNotof(input, C, 0);                 //checks for operators
                    if(FNO == -1)                                   //if last operator in the input string
                    {
                        infix.push(new Operator(input));            //pushed it into the queue
                        input = "";                                 //sets the input to empty
                        break;                                      //breaks
                    }
                    if(input.substr(0, FNO).size() > 1)
                    {
                        string Paren("Too Many Operators!");
                        throw(Paren);
                    }
                    infix.push(new Operator(input.substr(0, FNO))); //else, push the substring from 0 to where the type changes
                    input = input.substr(FNO);                      //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //break

            case 4 : FNO = FirstNotof(input, S, 0);                 //checks for spaces
                    if(FNO == -1)                                   //if last operator in the input string
                    {
                        input = "";                                 //sets the input to empty
                        break;                                      //breaks
                    }
                    input = input.substr(FNO);                      //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //breaks

            case 5 : infix.push(new Leftparen);                     //pushes a left parenthasis
                    input = input.substr(1);                        //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //breaks

            case 6 : infix.push(new Rightparen);                    //pushes a right parenthasis
                    input = input.substr(1);                        //set the input string to itself without the data just pushed into the infix queue
                    break;                                          //breaks
            case 7 : FNO = FirstNotof(input, Comma, 0);             //checks for comma
                    input = input.substr(FNO);
                    break;
            case 0 : throw(Paren);
                    break;
            default : throw(Paren);
                    break;
        }

    }
    return infix;
}


int zorg(string str, string Digits, string Letters, string Characters,
         string Space, string LeftP, string RightP, string Comma)                 //zorg takes in all the character sets as well as the input string
{
    if(Firstof(str, Digits, 0) == 0)                                //checks to see if the first character in the string is a digit
    {
        return 1;                                                   //if so, returns 1
    }else if(Firstof(str, Letters, 0) == 0)                         //checks to see if the first character in the string is a Letter
    {
        return 2;                                                   //if so, returns 2
    }else if(Firstof(str, Characters, 0) == 0)                      //checks to see if the first character in the string is a operator
    {
        return 3;                                                   //if so, returns a 3
    }else if(Firstof(str, Space, 0) == 0)                           //checks to see if the first character in the string is a space
    {
        string Paren("Error. Please remove all spaces.");
        throw(Paren);
        return 4;                                                   //if so, returns a 4
    }else if(Firstof(str, LeftP, 0) == 0)                           //checks to see if the first character in the string is a left parenthasis
    {
        return 5;                                                   //if so, returns a 5
    }else if(Firstof(str, RightP, 0) == 0)                          //checks to see if the first character in the string is a right parenthasis
    {
        return 6;                                                   //if so, returns a 6
    }else if(Firstof(str, Comma, 0) == 0)                          //checks to see if the first character in the string is a comma
    {
        return 7;                                                   //if so, returns a 7
    }else return 0;                                                 //else, returns a 0

}


int StrLen(string Input)                                            //gets the length of a string
{
    int counter = 0;                                                //counter
    for(int i = 0; Input[i]!=NULL; i++)                             //for loop
    {
        counter++;                                                  //increment counter
    }
    return counter;                                                 //returns counter
}

int StrFind(string str, char key)                                   //finds a char inside a string
{
    int pos = 0;                                                    //initialize int
    while(str[pos]!=NULL)                                           //continues until reached the end of the cstring str
    {
        if(str[pos]==key)                                           //checks if the char was found within the cstring
        {
            return pos;                                             //if found returns it's position
        }
        pos++;
    }
    return -1;
}

int Firstof(string str, string charset, int Pos)                    //finds the first character from a char set inside a string
{
    for(int i = Pos; i < StrLen(str); i++)                          //continues until size of cstring charset
        if(StrFind(charset, str[i])!=-1)                            //checks if str
        {
            return i;                                               //returns its position
        }
    return -1;                                                      //else if it doesnt find it, it returns -1
}

int FirstNotof(string str, string charset, int Pos)                 //finds the first character in a sequence not inside a string
{
    for(int i = Pos; str[i] != NULL; i++)                           //Used for going through cstring str[]
    {
        if(StrFind(charset, str[i])==-1)                            //this checks if it doesn't find the char in cstring
        {
            return i;
        }else if(StrFind(charset, str[i])!=-1)                      //this checks if it does find the char in cstring
        {
            continue;
        }
    }
    return -1;
}
int CountKey(string str, char key)
{
    int counter = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == key)
            counter++;
    }
    return counter;
}

#endif // STRINGTOKEN_H
