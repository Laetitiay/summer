#include <vector>
#include "Point.h"
#include "Defs.h"
#include "PrintOuts.h"
//
// Created by liron on 9/5/17.
//

#ifndef EX2_SHAPE_H
#define EX2_SHAPE_H
#define AREA_MODIFIER 2.0


/**
 * This class represents a general shape in the 2d realm.
 */
class Shape
{

public:

    /**
     * Constructs a shape
     * @param points vector of points for the shape
     * @param name name of the shape
     * @return a shape
     */
    Shape(std::vector<Point> points, std::string name);

    /**
     * Deconstructor
     */
    virtual ~Shape() = default;

    /**
     * Calculates the determinante of those three points (with an area modifier)
     * @param p1 first point
     * @param p2 second point
     * @param p3 third point
     * @return the area
     */
    static double threePointsCalc(const Point &p1, const Point &p2, const Point &p3);

    /**
     * Checks if a shape contains another shape
     * @return true iff this contains the given shape
     */
    bool contains(const Shape &)const;


    /**
     * Checks if the shape has an intersection with another shape
     * @return true iff this shape intersects with the given shape
     */
    bool hasIntersection(const Shape &)const;

    /**
     * the size of the shape (amount of points)
     * @return size of the shape
     */
    unsigned long size() const;

    /**
     * Checks if it is a valid shape
     * @return true iff it is a valid shape
     */
    virtual bool isValid() const = 0;

    /**
     * Calculates the area of the shape
     * @return area of the shape
     */
    virtual double calculateArea() const = 0;

    /**
     * Prints the shape to std::cout
     */
    virtual void print() const = 0;


protected:
    std::vector<Point> points;
    const std::string data_member;

};


#endif //EX2_SHAPE_H
