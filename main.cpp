/* 
 * File:   main.cpp
 * Author: ozielcarneiro
 *
 * Created on October 17, 2012, 9:44 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Map.h"
#include "Node.h"
#include "IO.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    IO io;
    string fileStr = io.fileToString("input.txt");
    while (fileStr.at(fileStr.size() - 1) == '\n') {
        fileStr = fileStr.substr(0, fileStr.size() - 1);
    }
    stringstream sstream;
    sstream << fileStr;

    vector<string> lines;

    string line;

    while (getline(sstream, line, '\n')) {
        lines.push_back(line);
    }

    vector<int> endRunLineIndex;
    for (int i = 0; i < lines.size(); i++) {
        if (lines.at(i).compare("") == 0) {
            endRunLineIndex.push_back(i);
        }
    }
    endRunLineIndex.push_back(lines.size());

    int runStart = 0;
    stringstream outStream;

    for (int i = 0; i < endRunLineIndex.size(); i++) {
        cout << "\n\nRun " << i+1 << " Pruning:\n\n";
        int runFinish = endRunLineIndex.at(i);
        stringstream runStream;
        for (int j = runStart; j < runFinish; j++) {
            runStream << lines.at(j) << endl;
        }
        Map map(runStream.str());
        Node node;
        node.setMap(&map);
        node.setTurn(1);
        node.setTurnPlayer();
        node.minmax(INT_MIN, INT_MAX);
        outStream << node.getPlay() << node.getValue() << endl << endl;
        
        runStart = runFinish + 1;
    }


    io.stringToFile("output.txt", outStream.str());


    


    return 0;
}

