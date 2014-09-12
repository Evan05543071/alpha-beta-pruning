/* 
 * File:   IO.cpp
 * Author: ozielcarneiro
 * 
 * Created on September 11, 2012, 10:11 AM
 */

#include "IO.h"
#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

IO::IO() {
}

IO::IO(const IO& orig) {
}

IO::~IO() {
}

void IO::stringToFile(string fileName, string text){
    ofstream file;
    file.open(fileName.c_str());
    if(file.is_open()){
        file << text;
        file.close();
    }else{
        cout << "Unable to open file";
    }
}

string IO::fileToString(string fileName){
    string line;
    string text = "";
    ifstream file;
    file.open(fileName.c_str());
    if(file.is_open()){
        while(getline(file,line)){
            text.append(line);
            text.append("\n");
        }
        file.close();
    }else{
        cout << "Unable to open file";
    }
    //cout << text << endl;
    return text;
}