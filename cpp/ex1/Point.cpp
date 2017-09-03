#include <algorithm>
#include "Point.h"
#include <math.h>

/**
 * creates a new point
 * @param x x cord
 * @param y y cord
 * @return a new points of (x,y)
 */
Point::Point(long int x, long int y)
{
    set(x, y);
}

/**
 * sets the x,y values of a point
 * @param x x cord
 * @param y y cord
 */
void Point::set(long x, long y)
{
    _x = x;
    _y = y;
}

/**
 * Gets the x cord of a point
 * @return x cord of a point
 */
long Point::getX() const
{
    return _x;
}

/**
 * Gets the y cord of a point
 * @return y cord of a point
 */
long Point::getY() const
{
    return _y;
}

/**
 * Creates a string of the point in the following style:
 * (x,y)
 * @return a string representing the point
 */
std::string Point::toString() const
{
    return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
}

/**
 * checks if the points are equals. That menas the X values and the Y values are equal.
 * @param rhs other point to compare
 * @return true iff both cords are the same.
 */
bool Point::operator==(const Point &rhs) const
{
    return _x == rhs._x && _y == rhs._y;
}

/**
 * checks if the points are unequals. That menas the X values and the Y values are not equal.
 * @param rhs other point to compare
 * @return false iff both cords are the same.
 */
bool Point::operator!=(const Point &rhs) const
{
    return !(operator==(rhs));
}

/**
 * Natural comparrison of the points. A point is smaller if it has lower x value. If the x value is the same
 * then the point with the lower value is smaller.
 * @param lhs left point
 * @param rhs right point
 * @return true iff lhs < rhs.
 */
bool Point::naturalCompare(Point &lhs, Point &rhs)
{
    if (lhs._x < rhs._x)
    {
        return true;
    }
    if (lhs._x > rhs._x)
    {
        return false;
    }
    return lhs._y < rhs._y;
}

