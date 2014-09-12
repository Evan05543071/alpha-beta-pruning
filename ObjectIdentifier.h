/* 
 * File:   ObjectIdentifier.h
 * Author: ozielcarneiro
 *
 * Created on October 18, 2012, 9:25 PM
 */

#ifndef OBJECTIDENTIFIER_H
#define	OBJECTIDENTIFIER_H

class ObjectIdentifier {
public:
    ObjectIdentifier(const int w, const int h);
    ObjectIdentifier(const ObjectIdentifier& orig);
    virtual ~ObjectIdentifier();
    void identify();
    void setBin(int **img);
    int getMaxOject();
    int getMaxOjectSize();
private:
    int **bin;
    int **label;
    int maxObject;
    int maxObjectSize;
    int w,h;
};

#endif	/* OBJECTIDENTIFIER_H */

