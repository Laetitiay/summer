//
// Created by liron on 9/5/17.
//

#include <math.h>
#include "Shape.h"


Shape::Shape(std::vector<Point> points)
{
    this->points = points;
}

double Shape::threePointsCalc(Point& p1, Point &p2, Point& p3)
{
//    return  (p2.getX()*p3.getY() - p2.getY() * p3.getX() - p1.getX() * p3.getY() + \
//    p3.getX() * p1.getY() + p1.getX() * p2.getY() - p2.getX() * p1.getY())/2.0;
    return ((p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX()))/2.0;

}

bool Shape::contains(Shape & other) {
    if (calculateArea() < other.calculateArea())
    {
        return false;
    }
    for (int i = 0; i < other.size(); ++i)
    {
        double sign = signbit(Shape::threePointsCalc(other.points[i], points[size() -1], points[0]));
        for (int j = 0; j < size() - 1; ++j)
        {
            if (sign != signbit(Shape::threePointsCalc(other.points[i], points[j], points[j + 1])))
            {
                return false;
            }
        }
    }
    return true;
}

unsigned long Shape::size(){
    return points.size();
}

bool Shape::hasIntersection(Shape & other)
{
    for (int i = 0; i < other.size(); ++i)
    {
        for (int j = 0; j < size(); ++j)
        {
//            double p1_s = Shape::threePointsCalc(points[j], other.points[i], other.points[(i + 1) % other.size()]);
//            double p2_s = Shape::threePointsCalc(points[(j + 1) % size()], other.points[i], other.points[(i + 1) % other.size()]);
//            double p3_s = Shape::threePointsCalc(other.points[i], points[j], points[(j + 1) % other.size()]);
//            double p4_s = Shape::threePointsCalc(other.points[(i + 1) % other.size()], other.points[j], other.points[(j + 1) % size()]);
            bool p1_sign = signbit(Shape::threePointsCalc(points[j], other.points[i], other.points[(i + 1) % other.size()]));
            bool p2_sign = signbit(Shape::threePointsCalc(points[(j + 1) % size()], other.points[i], other.points[(i + 1) % other.size()]));
            bool p3_sign = signbit(Shape::threePointsCalc(other.points[i], points[j], points[(j + 1) % size()]));
            bool p4_sign = signbit(Shape::threePointsCalc(other.points[(i + 1) % other.size()], points[j], points[(j + 1) % size()]));
            if(p1_sign != p2_sign && p3_sign != p4_sign)
            {
                return true;
            }
        }
    }
    return false;
}
