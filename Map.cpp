/* 
 * File:   Map.cpp
 * Author: ozielcarneiro
 * 
 * Created on October 17, 2012, 9:47 PM
 */

#include <vector>
#include <sstream>

#include "Map.h"

Map::Map() {
}

Map::Map(string inputData) {
    while (inputData.at(inputData.size() - 1) == '\n') {
        inputData = inputData.substr(0, inputData.size() - 1);
    }
    stringstream ss(inputData);
    vector<string> lines;
    string line;
    while (getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    int charSize = (lines.size() - 1)*(lines.size() - 1);
    char values[charSize];
    int j = 0;
    for (int i = 0; i < lines.size(); i++) {
        stringstream linestream(lines.at(i));
        if (i < 1) {
            linestream >> size;
        } else {
            for (int k = 0; k < lines.at(i).size(); k++) {
                if (lines.at(i).at(k) != ' ') {
                    values[j] = lines.at(i).at(k);
                    j++;
                }
            }
        }
    }
    map = new int *[size];
    for (int i = 0; i < charSize; i++) {
        int j = i%size;
        if(j==0){
            map[(i-j)/size] = new int[size];
        }
        if(values[i]=='r'){
            map[(i-j)/size][j] = 1;
        }else if(values[i]=='g'){
            map[(i-j)/size][j] = 2;
        }else{
            map[(i-j)/size][j] = 0;
        }
    }

}

Map::Map(const int size) {
    this->size = size;
    map = new int*[size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
        for (int j = 0; j < size; j++) {
            map[i][j] = 0;
        }
    }
}

Map::Map(const Map& orig) {
    size = orig.size;
    map = new int*[size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
        for (int j = 0; j < size; j++) {
            map[i][j] = orig.map[i][j];
        }
    }
}

Map::~Map() {
}

int Map::getSquare(int x, int y) {
    if (x >= 0 && y >= 0 && x < size && y < size) {
        return map[x][y];
    } else {
        return 0;
    }
}

bool Map::setSquare(int x, int y, int player) {
    if (map[x][y] == 0) {
        map[x][y] = player;
        return true;
    } else {
        return false;
    }
}

int Map::getSize() {
    return size;
}

bool Map::isFull() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (map[i][j] == 0) {
                return false;
            }
        }
    }
    return true;

}

bool Map::squareIsEmpty(int x, int y) {
    return (map[x][y] == 0);
}

char Map::getTurnPlayer() {
    int r = 0, g = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (map[i][j] == 1) {
                r++;
            } else if (map[i][j] == 2) {
                g++;
            }
        }
    }
    if (r == g) {
        return 'r';
    } else if (r > g) {
        return 'g';
    } else {
        return 'r';
    }
}