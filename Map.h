/* 
 * File:   Map.h
 * Author: ozielcarneiro
 *
 * Created on October 17, 2012, 9:47 PM
 */

#include <string>

using namespace std;

#ifndef MAP_H
#define	MAP_H

class Map {
public:
    Map();
    Map(string inputData);
    Map(const int size);
    Map(const Map& orig);
    virtual ~Map();
    int getSquare(int x, int y);
    bool setSquare(int x, int y, int player);
    bool isFull();
    int getSize();
    bool squareIsEmpty(int x, int y);
    char getTurnPlayer();
private:
    int size;
    int **map;
};

#endif	/* MAP_H */

