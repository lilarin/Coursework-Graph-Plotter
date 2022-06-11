//
// Created by User on 09.06.2022.
//

#ifndef MAIN_CPP_UTILITY_H
#define MAIN_CPP_UTILITY_H
#include <sstream>

float roundValue(float var) {   // round the number down to a hundredth
    float value = (int)(var * 100 + .5);
    return value / 100;
}

string intToString(float number) {
    stringstream ss;    // create a stringstream
    string str;         // create string
    ss << number;       // add number to the stream
    ss >> str;          // push the contents onto a string
    return str;         // return the string
}

#endif //MAIN_CPP_UTILITY_H
