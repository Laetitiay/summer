// Point.h

#ifndef POINT_H
#define POINT_H

#include <string>

/**
 *  A point class.
 *  This class represents a point with (x,y) coordinates.
 */
class Point
{

public:
    Point(long x, long y);
    ~Point() = default;
    void set(long x, long y);
    std::string toString()const;
    bool operator==(const Point &rhp)const;

private:
    long _x;
    long _y;

};


#endif
