/* 
 * File:   IO.h
 * Author: ozielcarneiro
 *
 * Created on September 11, 2012, 10:11 AM
 */

#include <string>

using namespace std;

#ifndef IO_H
#define	IO_H

class IO {
public:
    IO();
    IO(const IO& orig);
    virtual ~IO();
    void stringToFile(string fileName, string text);
    string fileToString(string fileName);
private:

};

#endif	/* IO_H */

