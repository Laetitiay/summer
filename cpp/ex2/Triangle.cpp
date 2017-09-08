//
// Created by liron on 9/5/17.
//

#include "Triangle.h"
#include <cmath>

Triangle::Triangle(std::vector<Point> points) : Shape(points)
{

}


bool Triangle::isValid()
{
    return !Shape::threePointsCalc(points[0], points[1], points[2]) < EPSILON;
}

double Triangle::calculateArea()
{
    return std::abs(Shape::threePointsCalc(points[0], points[1], points[2]));
}

