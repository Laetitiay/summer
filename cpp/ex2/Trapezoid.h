//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRAPEZOID_H
#define EX2_TRAPEZOID_H


#include "Shape.h"
#include "Triangle.h"
#include <cmath>

#define TRAPEZOID_NAME "Trapezoid"

/**
 * This class represents a trapezoid in the 2d realm.
 */
class Trapezoid : public Shape
{
public:

    /**
     * Trapezoid constructor
     * @param points vector of points of the shape
     * @return a new Trapezoid
     */
    Trapezoid(std::vector<Point> points);

    /**
     * Default destructor.
     */
    ~Trapezoid() override = default;

    /**
     * Is it a valid trapezoid?
     * @return true iff the points represent a valid trapezoid.
     */
    bool isValid() const;

    /**
     * calculates the area of the Triangle
     * @return area of triangle
     */
    double calculateArea() const;

    /**
     * Prints the area of the trapezoid to std::cout.
     */
    void print() const;


private:
    /**
     * Checks if the trapezoid is parralell to the x axis.
     * @return true iff it is paralel to x axis.
     */
    bool _isParallelToXAxis() const;

    /**
     * Checks if the trapezoid is an hourglass.
     * @return true iff it is an hourglass.
     */
    bool _isNotHourglass() const;
};


#endif //EX2_TRAPEZOID_H
