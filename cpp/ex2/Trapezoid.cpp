//
// Created by liron on 9/5/17.
//

#include "Trapezoid.h"


Trapezoid::Trapezoid(std::vector<Point> points) : Shape(points)
{
}

bool Trapezoid::isValid()
{
    //3

    /**
     * 1. not hourglass: one must be true
     * p1_x > p2_x => p4_x > p3_x
     * p2_x > p1_x => p3_x > p4_x
     */
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

