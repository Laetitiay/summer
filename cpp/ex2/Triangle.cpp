//
// Created by liron on 9/5/17.
//

#include "Triangle.h"
#include <cmath>

/**
 * Trinalge constructor
 * @param points vector of points of the shape
 * @return a new Triangle
 */
Triangle::Triangle(std::vector<Point> points) : Shape(points, TRIANGLE_NAME)
{

}


/**
 * Is it a valid triangle?
 * @return true iff the points represent a valid triangle.
 */
bool Triangle::isValid() const
{
    return std::fabs(Shape::threePointsCalc(points[0], points[1], points[2])) > EPSILON;
}

/**
 * calculates the area of the Triangle
 * @return area of triangle
 */
double Triangle::calculateArea() const
{
    return std::abs(Shape::threePointsCalc(points[0], points[1], points[2]));
}

/**
 * Prints the triangle to std::cout.
 */
void Triangle::print() const
{
    printTriangle(points[0].getX(), points[0].getY(),
                  points[1].getX(), points[1].getY(),
                  points[2].getX(), points[2].getY()

    );
}
