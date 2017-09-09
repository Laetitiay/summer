//
// Created by liron on 9/5/17.
//

#include "Trapezoid.h"


Trapezoid::Trapezoid(std::vector<Point> points) : Shape(points)
{
}

bool Trapezoid::isValid()
{

    return isParallelToXAxis() && isNotHourglass();
}

double Trapezoid::calculateArea()
{
    double sum = 0;
    sum += std::abs(Shape::threePointsCalc(points[0], points[1], points[2]));
    sum += std::abs(Shape::threePointsCalc(points[0], points[2], points[3]));
    return sum;
}


/**
 * 1. not hourglass: one must be true
 * p1_x > p2_x => p4_x > p3_x
 * p2_x > p1_x => p3_x > p4_x
 */
bool Trapezoid::isNotHourglass()const
{
    if ((points[0].getX() > points[2].getX() && points[3].getX() > points[2].getX()) )
    {
        return true;
    }
    return points[1].getX() > points[0].getX() && points[2].getX() > points[3].getX();
}

/**
 * Parralel to x-axis
 * iff
 */
bool Trapezoid::isParallelToXAxis()const
{
    return !(points[0].getY() != points[1].getY() || points[2].getY() != points[3].getY());
}

void Trapezoid::print()
{
    printTrapezoid(points[0].getX(),points[0].getY(),
                  points[1].getX(),points[1].getY(),
                  points[2].getX(), points[2].getY(),
                    points[3].getX(), points[3].getY()
    );
}
