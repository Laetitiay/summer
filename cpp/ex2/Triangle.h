//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRIANGLE_H
#define EX2_TRIANGLE_H


#include "Shape.h"
#include <vector>

#define SHAPE_NAME "Triangle"

class Triangle : public Shape
{
public:
    Triangle(std::vector<Point> points);
    bool isValid();
    double calculateArea() const;
};


#endif //EX2_TRIANGLE_H
