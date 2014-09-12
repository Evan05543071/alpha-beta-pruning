/* 
 * File:   Node.h
 * Author: ozielcarneiro
 *
 * Created on October 17, 2012, 9:45 PM
 */

#include "Map.h"
#include <vector>
#include <sstream>

using namespace std;

#ifndef NODE_H
#define	NODE_H


class Node {
public:
    Node();
    Node(const Node& orig);
    virtual ~Node();
    int minmax(int alpha, int beta);
    int utility();
    void setMap(Map *map);
    void setTurn(int turn);
    void setTurnPlayer();
    void successors();
    void play(Node *play,int x, int y);
    string getPlay();
    int getValue();
private:
    Map* map;
    char turnPlayer;
    int turn;//1=max 2=min
    vector<int> xPlay;
    vector<int> yPlay;
    int alpha;
    int beta;
    int minmaxValue;
    vector<int> xSuc;
    vector<int> ySuc;
};

#endif	/* NODE_H */

