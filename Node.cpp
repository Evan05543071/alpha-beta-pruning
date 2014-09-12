/* 
 * File:   Node.cpp
 * Author: ozielcarneiro
 * 
 * Created on October 17, 2012, 9:45 PM
 */
#include <iostream>
#include <sstream>

#include "Node.h"
#include "Map.h"
#include "ObjectIdentifier.h"

using namespace std;

Node::Node() {
}

Node::Node(const Node& orig) {
    Map* map = orig.map;
    turnPlayer = orig.turnPlayer;
    turn = orig.turn;
    xPlay = orig.xPlay;
    yPlay = orig.yPlay;
    alpha = orig.alpha;
    beta = orig.beta;
    minmaxValue = orig.minmaxValue;
    xSuc = orig.xSuc;
    ySuc = orig.ySuc;
}

Node::~Node() {
}

int Node::minmax(int alpha, int beta) {
    this->alpha = alpha;
    this->beta = beta;
    if ((*map).isFull()) {
        minmaxValue = utility();
        return minmaxValue;
    } else {
        if (turn == 1) {//MAX TURN
            minmaxValue = INT_MIN;
            successors();
            for (int i = 0; i < xSuc.size(); i++) {
                Node next;
                play(&next, xSuc.at(i), ySuc.at(i));
                int nextMinMax = next.minmax(this->alpha, this->beta);
                if (nextMinMax > minmaxValue) {
                    xPlay.clear();
                    yPlay.clear();
                    xPlay.push_back(xSuc.at(i));
                    yPlay.push_back(ySuc.at(i));
                    minmaxValue = nextMinMax;
                } else if (nextMinMax == minmaxValue) {
                    xPlay.push_back(xSuc.at(i));
                    yPlay.push_back(ySuc.at(i));
                }
                if (minmaxValue>this->alpha) {
                    this->alpha = minmaxValue;
                    alpha = minmaxValue;
                }
                
                //pruning
                if (minmaxValue>this->beta) {
                    if (i < xSuc.size()-1) {
                        stringstream pruningOut;
                        pruningOut << "Player " << turnPlayer << "'s turn: alpha = ";
                        pruningOut << this->alpha << "; beta = " << this->beta << "; all moves: ";
                        for (int j = 0; j < xSuc.size(); j++) {
                            pruningOut << "<" << xSuc.at(j) << "," << ySuc.at(j) << ">";
                            if (j != xSuc.size() - 1) {
                                pruningOut << ",";
                            } else {
                                pruningOut << "; ";
                            }
                        }
                        pruningOut << "pruned moves: ";
                        for (int j = i + 1; j < xSuc.size(); j++) {
                            pruningOut << "<" << xSuc.at(j) << "," << ySuc.at(j) << ">";
                            if (j != xSuc.size() - 1) {
                                pruningOut << ",";
                            } else {
                                pruningOut << "; ";
                            }
                        }
                        cout << pruningOut.str() << endl;
                    }
                    return minmaxValue;
                }
                //end pruning
                
            }
            return minmaxValue;
        } else {//MIN TURN
            minmaxValue = INT_MAX;
            successors();
            for (int i = 0; i < xSuc.size(); i++) {
                Node next;
                play(&next, xSuc.at(i), ySuc.at(i));
                if (&next == NULL) {
                    continue;
                }
                int nextMinMax = next.minmax(this->alpha, this->beta);
                if (nextMinMax < minmaxValue) {
                    xPlay.clear();
                    yPlay.clear();
                    xPlay.push_back(xSuc.at(i));
                    yPlay.push_back(ySuc.at(i));
                    minmaxValue = nextMinMax;
                }else{
                    xPlay.push_back(xSuc.at(i));
                    yPlay.push_back(ySuc.at(i));
                }
                if (minmaxValue<this->beta) {
                    this->beta = minmaxValue;
                    beta = minmaxValue;
                }
                
                //pruning
                if (minmaxValue < this->alpha) {
                    if (i < xSuc.size()-1) {
                        stringstream pruningOut;
                        pruningOut << "Player " << turnPlayer << "'s turn: alpha = ";
                        pruningOut << this->alpha << "; beta = " << this->beta << "; all moves: ";
                        for (int j = 0; j < xSuc.size(); j++) {
                            pruningOut << "<" << xSuc.at(j) << "," << ySuc.at(j) << ">";
                            if (j != xSuc.size() - 1) {
                                pruningOut << ",";
                            } else {
                                pruningOut << "; ";
                            }
                        }
                        pruningOut << "pruned moves: ";
                        for (int j = i + 1; j < xSuc.size(); j++) {
                            pruningOut << "<" << xSuc.at(j) << "," << ySuc.at(j) << ">";
                            if (j != xSuc.size() - 1) {
                                pruningOut << ",";
                            } else {
                                pruningOut << "; ";
                            }
                        }
                        cout << pruningOut.str() << endl;
                    }
                    return minmaxValue;
                }
                
                //end pruning
            }
            return minmaxValue;
        }
    }
    return minmaxValue;
}

int Node::utility() {
    int size = (*map).getSize();
    int **redBin = new int*[size];
    int **goldBin = new int*[size];
    for (int i = 0; i < size; i++) {
        redBin[i] = new int[size];
        goldBin[i] = new int[size];
        for (int j = 0; j < size; j++) {
            if ((*map).getSquare(i, j) == 1) {
                redBin[i][j] = 1;
                goldBin[i][j] = 0;
            } else if ((*map).getSquare(i, j) == 2) {
                redBin[i][j] = 0;
                goldBin[i][j] = 1;
            } else {
                redBin[i][j] = 0;
                goldBin[i][j] = 0;
            }
        }
    }

    int redScore = 0;
    int goldScore = 0;
    ObjectIdentifier oi(size, size);
    oi.setBin(redBin);
    oi.identify();
    redScore = oi.getMaxOjectSize();
    oi.setBin(goldBin);
    oi.identify();
    goldScore = oi.getMaxOjectSize();
    if ((turn == 1 && turnPlayer == 'r') || (turn == 2 && turnPlayer == 'g')) {
        return redScore - goldScore;
    } else {
        return goldScore - redScore;
    }
    return 0;
}


void Node::setMap(Map* map) {
    this->map = map;
}

void Node::setTurn(int turn) {
    this->turn = turn;
}

void Node::setTurnPlayer() {
    turnPlayer = (*map).getTurnPlayer();
}

void Node::successors() {
    for (int i = 0; i < (*map).getSize(); i++) {
        for (int j = 0; j < (*map).getSize(); j++) {
            if ((*map).squareIsEmpty(i, j)) {
                xSuc.push_back(i);
                ySuc.push_back(j);
            }
        }
    }
}

void Node::play(Node *play, int x, int y) {
    int playerInt = 0;
    if (turnPlayer == 'r') {
        (*play).turnPlayer = 'g';
        playerInt = 1;
    } else {
        (*play).turnPlayer = 'r';
        playerInt = 2;
    }
    if (turn == 1) {
        (*play).turn = 2;
    } else {
        (*play).turn = 1;
    }
    (*play).alpha = alpha;
    (*play).beta = beta;
    (*play).map = new Map(*map);
    (*play).map->setSquare(x, y, playerInt);
}

string Node::getPlay() {
    stringstream sstream;
    for (int i = 0; i < xPlay.size(); i++) {
        sstream << "(" << xPlay.at(i) << "," << yPlay.at(i) << ")";
    }
    return sstream.str();
}

int Node::getValue(){
    return minmaxValue;
}