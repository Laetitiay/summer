//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRAPEZOID_H
#define EX2_TRAPEZOID_H


#include "Shape.h"
#include "Triangle.h"
#include <cmath>

class Trapezoid : public Shape
{
    bool isValid();
    double calculateArea() ;

public:
    Trapezoid(std::vector<Point> points);
private:
    bool isParallelToXAxis()const;
    bool isNotHourglass()const;
};


#endif //EX2_TRAPEZOID_H
