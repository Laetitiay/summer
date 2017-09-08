//
// Created by liron on 9/5/17.
//

#include "Shape.h"


Shape::Shape(std::vector<Point> points)
{
    this->points = points;
}

double Shape::threePointsCalc(Point p1, Point p2, Point p3)
{
    return  (p2._x*p3._y - p2._y * p3._x - p1._x * p3._y + p3._x * p1._y + p1._x * p2._y - p2._x * p1._y)/2;
}

bool Shape::contains(const Shape & other) const {
    if (calculateArea() < other.calculateArea())
    {
        return false;
    }
    for (int i = 0; i < size(); ++i) {

    }
    Shape::threePointsCalc()
    return false;
}

unsigned long Shape::size()const {
    return points.size();
}
