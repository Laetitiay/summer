//
// Created by liron on 9/7/17.
//

#ifndef EX2_SHAPEFACTORY_H
#define EX2_SHAPEFACTORY_H


#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"

#define TRAPEZOID 't'
#define TRIANGLE 'T'


class ShapeFactory
{

public:
    static Shape *createShape(char shapeType, std::vector<Point> points);
};


#endif //EX2_SHAPEFACTORY_H
