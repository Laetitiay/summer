// Point.h


#ifndef POINT_H
#define POINT_H

#include "Defs.h"
#include <string>
#define POINT_NAME "Point"

/**
 *  A point class.
 *  This class represents a point with (x,y) coordinates.
 */
class Point
{

public:


/**
 * creates a new point
 * @param x x cord
 * @param y y cord
 * @return a new points of (x,y)
 */
    Point() = default;

/**
 * sets the x,y values of a point
 * @param x x cord
 * @param y y cord
 */
    Point(CordType x, CordType y);



/**
 * the copy Constructor
 * @param point the point we want to copy
 */
    Point(const Point &point) = default;

/**
 * Deletes a point
 */
    ~Point() = default;

/**
 * sets the x,y values of a point
 * @param x x cord
 * @param y y cord
 */
    void set(CordType x, CordType y);

/**
 * Creates a string of the point in the following style:
 * (x,y)
 * @return a string representing the point
 */
    std::string toString() const;

/**
 * checks if the points are equals. That menas the X values and the Y values are equal.
 * @param rhs other point to compare
 * @return true iff both cords are the same.
 */
    bool operator==(const Point &rhs) const;

/**
 * checks if the points are unequals. That menas the X values and the Y values are not equal.
 * @param rhs other point to compare
 * @return false iff both cords are the same.
 */
    bool operator!=(const Point &rhs) const;

/**
 * operator=
 * @param point the point we want to copy
 * @return the point we copy, the same parm of point.
 */
    Point& operator=(const Point &point) = default;

/**
 * Gets the x cord of a point
 * @return x cord of a point
 */
    CordType getX() const;

/**
 * Gets the y cord of a point
 * @return y cord of a point
 */
    CordType getY() const;

private:
    CordType _x;
    CordType _y;
    std::string data_member;
};


#endif
