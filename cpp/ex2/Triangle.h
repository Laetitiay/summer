//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRIANGLE_H
#define EX2_TRIANGLE_H


#include "Shape.h"
#include <vector>

#define TRIANGLE_NAME "Triangle"

class Triangle : public Shape
{
public:
    Triangle(std::vector<Point> points);

    bool isValid() override;

    double calculateArea() override;

    void print();
};


#endif //EX2_TRIANGLE_H
