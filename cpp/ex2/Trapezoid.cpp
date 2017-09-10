#include "Trapezoid.h"


/**
 * Trapezoid constructor
 * @param points vector of points of the shape
 * @return a new Trapezoid
 */
Trapezoid::Trapezoid(std::vector<Point> points) : Shape(points, TRAPEZOID_NAME)
{
}

/**
 * Is it a valid trapezoid?
 * @return true iff the points represent a valid trapezoid.
 */
bool Trapezoid::isValid() const
{

    return _isParallelToXAxis() && _isNotHourglass();
}

/**
 * calculates the area of the Triangle
 * @return area of triangle
 */
double Trapezoid::calculateArea() const
{
    double sum = 0;
    sum += std::abs(Shape::threePointsCalc(points[0], points[1], points[2]));
    sum += std::abs(Shape::threePointsCalc(points[0], points[2], points[3]));
    return sum;
}


/**
 * Checks if the trapezoid is an hourglass.
 * one must be true
 * p1_x > p2_x => p4_x > p3_x
 * p2_x > p1_x => p3_x > p4_x
 * @return true iff it is an hourglass.
 */
bool Trapezoid::_isNotHourglass() const
{
    if ((points[0].getX() > points[2].getX() && points[3].getX() > points[2].getX()))
    {
        return true;
    }
    return points[1].getX() > points[0].getX() && points[2].getX() > points[3].getX();
}

/**
 * Checks if the trapezoid is parralell to the x axis.
 * @return true iff it is paralel to x axis.
 */
bool Trapezoid::_isParallelToXAxis() const
{
    return !(points[0].getY() != points[1].getY() || points[2].getY() != points[3].getY());
}

/**
 * Prints the area of the trapezoid to std::cout.
 */
void Trapezoid::print() const
{
    printTrapezoid(points[0].getX(), points[0].getY(),
                   points[1].getX(), points[1].getY(),
                   points[2].getX(), points[2].getY(),
                   points[3].getX(), points[3].getY()
    );
}
