//
// Created by liron on 8/30/17.
//

#ifndef EX1_VECTOR_H
#define EX1_VECTOR_H


#include "Point.h"

class PointVector
{
public:
    PointVector();
    PointVector(PointVector& pv);
    ~PointVector();
    bool add(Point &p);
    bool remove(Point &p);
    int getSize();

private:
};


#endif //EX1_VECTOR_H
