// Point.h


#ifndef POINT_H
#define POINT_H
#include "Defs.h"
#include <string>

/**
 *  A point class.
 *  This class represents a point with (x,y) coordinates.
 */
class Point
{

public:

//friend double threePointsCalc(Point &p1, Point &p2, Point &p3);

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
 * Gets the x cord of a point
 * @return x cord of a point
 */
    CordType getX() const;

/**
 * Gets the y cord of a point
 * @return y cord of a point
 */
    CordType getY() const;

/**
 * Natural comparrison of the points. A point is smaller if it has lower x value. If the x value is the same
 * then the point with the lower value is smaller.
 * @param lhs left point
 * @param rhs right point
 * @return true iff lhs < rhs.
 */
    static bool naturalCompare(Point &lhs, Point &rhs);

private:
    CordType _x;
    CordType _y;
};


#endif
