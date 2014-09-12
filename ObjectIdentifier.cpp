/* 
 * File:   ObjectIdentifier.cpp
 * Author: ozielcarneiro
 * 
 * Created on October 18, 2012, 9:25 PM
 */

#include <vector>
#include <iostream>

#include "ObjectIdentifier.h"


using namespace std;

ObjectIdentifier::ObjectIdentifier(const int w, const int h) {

    bin = new int*[h + 2];
    label = new int*[h + 2];
    for (int i = 0; i < h + 2; i++) {
        bin[i] = new int[w + 2];
        label[i] = new int[w + 2];
        for (int j = 0; j < w+2; j++) {
            bin[i][j] = 0;
            label[i][j] = 0;
        }

    }
    this->w = w;
    this->h = h;
}

ObjectIdentifier::ObjectIdentifier(const ObjectIdentifier& orig) {
}

ObjectIdentifier::~ObjectIdentifier() {
}

void ObjectIdentifier::identify() {

    int objCounter = 0;

    for (int i = 0; i < h + 2; i++) {
        for (int j = 0; j < w + 2; j++) {
            label[i][j] = 0;
        }
    }

    vector<int> queueX;
    vector<int> queueY;

    for (int i = 1; i < h + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            if (bin[i][j] != 0) {
                if (label[i][j] == 0) {
                    objCounter++;
                    queueX.push_back(i);
                    queueY.push_back(j);
                    while (!queueX.empty()) {
                        int x = queueX.at(queueX.size() - 1);
                        int y = queueY.at(queueY.size() - 1);
                        label[x][y] = objCounter;
                        queueX.pop_back();
                        queueY.pop_back();
                        
                        if (bin[x - 1][y] == 1 && label[x - 1][y] == 0) {
                            bool flag = 0;
                            for (int k = 0; k < queueX.size(); k++) {
                                if (queueX.at(k) == x - 1 && queueY.at(k) == y) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (!flag) {
                                queueX.push_back(x - 1);
                                queueY.push_back(y);
                            }
                        }
                        
                        if (bin[x][y - 1] == 1 && label[x][y - 1] == 0) {
                            bool flag = 0;
                            for (int k = 0; k < queueX.size(); k++) {
                                if (queueX.at(k) == x && queueY.at(k) == y - 1) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (!flag) {
                                queueX.push_back(x);
                                queueY.push_back(y - 1);
                            }
                        }
                        if (bin[x][y + 1] == 1 && label[x][y + 1] == 0) {
                            bool flag = 0;
                            for (int k = 0; k < queueX.size(); k++) {
                                if (queueX.at(k) == x && queueY.at(k) == y + 1) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (!flag) {
                                queueX.push_back(x);
                                queueY.push_back(y + 1);
                            }
                        }
                        
                        if (bin[x + 1][y] == 1 && label[x + 1][y] == 0) {
                            bool flag = 0;
                            for (int k = 0; k < queueX.size(); k++) {
                                if (queueX.at(k) == x + 1 && queueY.at(k) == y) {
                                    flag = 1;
                                    break;
                                }
                            }
                            if (!flag) {
                                queueX.push_back(x + 1);
                                queueY.push_back(y);
                            }
                        }
                        
                    }
                }
            }
        }
    }
    
    int objSize[objCounter+1];
    
    for (int i = 0; i < objCounter+1; i++) {
        objSize[i] = 0;
    }

    for (int i = 0; i < h+2; i++) {
        for (int j = 0; j < w+2; j++) {
            if(label[i][j]!=0){
                objSize[label[i][j]]++;
            }
        }
    }
    
    maxObject = 0;
    maxObjectSize = 0;
    for (int i = 0; i < objCounter+1; i++) {
        if(objSize[i]>maxObjectSize){
            maxObject = i;
            maxObjectSize = objSize[i];
        }
    }
}

int ObjectIdentifier::getMaxOject() {
    return maxObject;
}

int ObjectIdentifier::getMaxOjectSize() {
    return maxObjectSize;
}

void ObjectIdentifier::setBin(int** img){
    for (int i = 1; i < h+1; i++) {
        for (int j = 1; j < w+1; j++) {
            bin[i][j] = img[i-1][j-1];
        }
    }
}