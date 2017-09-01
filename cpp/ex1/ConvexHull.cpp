#include <iostream>
#include <math.h>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

static Point minPoint;
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

void swapPoints(Point *a, Point *b)
{
    Point c = *a;
    *a = *b;
    *b = c;
}

Point* findMin(Point* arr, int size)
{
    Point* min = &arr[1];
    for (int i = 2; i <= size; ++i)
    {
        if(arr[i].getY() < min->getY())
        {
            min = &arr[i];
        }
        else if (arr[i].getY() == min->getY() && arr[i].getX() < min->getX())
        {
            min = &arr[i];
        }
    }
    return min;
}


long ccw(Point &p1, Point &p2, Point &p3)
{
    return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
}



double angle(Point &p)
{
    long deltaX = minPoint.getX() - p.getX();
    long deltaY = minPoint.getY() - p.getY();
    //return atan(deltaY/deltaX);
    return atan2(deltaY, deltaX);
}

bool angleCompare(Point &p1, Point &p2)
{
    return angle(p1) < angle(p2);
}

PointSet* createConvexHull(PointSet& set)
{

    Point* points = set.toArrayWithPadding(1);
    swapPoints(&points[1], findMin(points, set.size()));
    minPoint = points[1];
    if(set.size() > 2)
    {
        std::sort(points + 2, points + set.size() + 1, angleCompare);
    }
    points[0] = points[set.size()];
    int m = 1;
    for (int i = 2 ; i < set.size() ; ++i)
    {
        while(ccw (points[m-1], points[m], points[i]) <= 0)
        {
            if (m > 1)
            {
                m-= 1;
                continue;
            }
            else if (i == set.size())
            {
                break;
            }
            else
            {
                i+=1;
            }
        }
        m += 1;
        swapPoints(&points[m] , &points[i]);
    }
    PointSet* ret = new PointSet;
    for (int j = 0; j <= m ; ++j) {
        ret->add(points[j]);
    }
    return ret;
}

int main()
{
    PointSet set = getInput();
    PointSet* convex = createConvexHull(set);
    std::cout << convex->toString();
    // TODO: every "new" should have "delete".
}