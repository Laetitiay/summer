#include <algorithm>
#include "Point.h"

// constructor of point
Point::Point(long int x, long int y)
{
    set(x,y);
}

void Point::set(long x, long y)
{
    _x = x;
    _y = y;
}

long Point::getX()const{
    return _x;
}

long Point::getY()const {
    return _y;
}

std::string Point::toString()const
{
    return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
}

bool Point::operator==(const Point &rhs)const
{
    return _x == rhs._x && _y == rhs._y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(operator==(rhs));
}

bool Point::operator<(const Point &rhs) const {

}


bool Point::naturalCompare(Point &lhs, Point &rhs)
{
    if(lhs._x < rhs._x)
    {
        return true;
    }
    if(lhs._x > rhs._x)
    {
        return false;
    }
    return lhs._y < rhs._y;
}
