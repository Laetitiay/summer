#include <iostream>
#include "Point.h"
#include "PointSet.h"

PointSet& getInput()
{
    PointSet *ps = new PointSet{};
    long x,y;
    char delim;
    while(!std::cin.eof() && std::cin >> x >> delim >> y)
    {
        ps->add(Point{x,y});
    }
    return *ps;
}

Point findMin(PointSet& set)
{
    // TODO
}

int ccw(Point &p1, Point &p2, Point &p3)
{
    return 0;
}

PointSet& createConvexHull(PointSet& set)
{
    Point min = findMin(set);
    // TODO CREATE ARRAY AND SORT BY MIN ANGLE.
    // CAN ADD angle && distance to points

    int m = 1;
    for (int i = 2 ; i < size ; ++i)
    {
        while(ccw (points[m-1], points[m], points[i]) <= 0)
        {
            if (m > 1)
            {
                m-= 1;
                continue;
            }
            if (i == size)
            {
                break;
            }
            i+=1;

        }
        m += 1;
        swap(points[m] , points[i]);
    }

}

int main()
{
    PointSet set = getInput();
    std::cout << set.toString();
}