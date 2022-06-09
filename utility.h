//
// Created by User on 09.06.2022.
//

#ifndef MAIN_CPP_UTILITY_H
#define MAIN_CPP_UTILITY_H
#include <unistd.h>

float roundValue(float var) {   // round the number down to a hundredth
    float value = (int)(var * 100 + .5);
    return value / 100;
}

string intToString(float number) {
    stringstream ss;// create a stringstream
    string str;     // create string
    ss << number;   // add number to the stream
    ss >> str;      // push the contents onto a string
    return str;     // return the string
}

//--------------------------------------------------------------
// Attention, there may be problems with other compilers here!!!
//--------------------------------------------------------------
string getProjectDirectory() {
    char temp[100];
    string tempString = getcwd(temp, 256),projectDirectory; // get the path to the project
    replace(projectDirectory.begin(), projectDirectory.end(), '\\', '/'); // replace the slashes
    for (int i = 0; i < tempString.length()-18; i++) { // copy only the necessary part of the path,
        projectDirectory += tempString[i];             // because in Clion the path goes deep into the project
    }
    return projectDirectory;
}


#endif //MAIN_CPP_UTILITY_H
