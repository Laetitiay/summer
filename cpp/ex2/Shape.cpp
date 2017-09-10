//
// Created by liron on 9/5/17.
//

#include <math.h>
#include "Shape.h"


/**
 * Constructs a shape
 * @param points vector of points for the shape
 * @param name name of the shape
 * @return a shape
 */
Shape::Shape(std::vector<Point> points, std::string name) : data_member{name}
{
    this->points = points;
}

/**
 * Calculates the determinante of those three points (with an area modifier)
 * @param p1 first point
 * @param p2 second point
 * @param p3 third point
 * @return the area
 */
double Shape::threePointsCalc(const Point &p1, const Point &p2, const Point &p3)
{
    return ((p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX())) /
           AREA_MODIFIER;

}

/**
 * Checks if a shape contains another shape
 * @return true iff this contains the given shape
 */
bool Shape::contains(const Shape &other)const
{
    if (calculateArea() < other.calculateArea())
    {
        return false;
    }
    for (unsigned i = 0; i < other.size(); ++i)
    {
        double sign = signbit(Shape::threePointsCalc(other.points[i], points[size() - 1], points[0]));
        for (unsigned j = 0; j < size() - 1; ++j)
        {
            if (sign != signbit(Shape::threePointsCalc(other.points[i], points[j], points[j + 1])))
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * the size of the shape (amount of points)
 * @return size of the shape
 */
unsigned long Shape::size() const
{
    return points.size();
}

/**
 * Checks if the shape has an intersection with another shape
 * @return true iff this shape intersects with the given shape
 */
bool Shape::hasIntersection(const Shape &other)const
{
    for (unsigned i = 0; i < other.size(); ++i)
    {
        for (unsigned j = 0; j < size(); ++j)
        {
            bool p1_sign = signbit(Shape::threePointsCalc(
                    points[j], other.points[i], other.points[(i + 1) % other.size()]));
            bool p2_sign = signbit(Shape::threePointsCalc(
                    points[(j + 1) % size()], other.points[i], other.points[(i + 1) % other.size()]));
            bool p3_sign = signbit(Shape::threePointsCalc(
                    other.points[i], points[j], points[(j + 1) % size()]));
            bool p4_sign = signbit(Shape::threePointsCalc(
                    other.points[(i + 1) % other.size()], points[j], points[(j + 1) % size()]));
            if (p1_sign != p2_sign && p3_sign != p4_sign)
            {
                return true;
            }
        }
    }
    return false;
}
