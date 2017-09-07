//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRAPEZOID_H
#define EX2_TRAPEZOID_H


#include "Shape.h"
#include "Triangle.h"
#include <cmath>

class Trapezoid : Shape
{
    Trapezoid(std::vector<Point> points);
    bool isValid();
    double calculateArea() const;

};


#endif //EX2_TRAPEZOID_H
