//
// Created by liron on 9/5/17.
//

#include "Trapezoid.h"


Trapezoid::Trapezoid(std::vector<Point> points) : Shape(points)
{
}

bool Trapezoid::isValid()
{
    return false;
}

double Trapezoid::calculateArea() const
{
    double sum = 0;
    for (int i = 0; i <= 1; ++i)
    {
        sum += std::abs(Shape::threePointsCalc(points[0 + i], points[1 + i], points[2 + i]));
    }
    return sum;
}

