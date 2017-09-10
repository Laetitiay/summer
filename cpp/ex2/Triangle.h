//
// Created by liron on 9/5/17.
//

#ifndef EX2_TRIANGLE_H
#define EX2_TRIANGLE_H


#include "Shape.h"
#include <vector>

#define TRIANGLE_NAME "Triangle"

/**
 * A triangle in the 2d realm.
 */
class Triangle : public Shape
{
public:
    /**
     * Trinalge constructor
     * @param points vector of points of the shape
     * @return a new Triangle
     */
    Triangle(std::vector<Point> points);

    /**
     * Default destructor.
     */
    ~Triangle() override = default;

    /**
     * Is it a valid triangle?
     * @return true iff the points represent a valid triangle.
     */
    bool isValid() const override;

    /**
     * calculates the area of the Triangle
     * @return area of triangle
     */
    double calculateArea() const override;


    /**
     * Prints the triangle to std::cout.
     */
    void print() const;
};


#endif //EX2_TRIANGLE_H
