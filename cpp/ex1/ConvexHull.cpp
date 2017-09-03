#include <iostream>
#include <math.h>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

#define MIN_CONVEX_HULL_SIZE 2

static Point minPoint; // minimum point in the convex.

/**
 * Receives input from the user in the form of: "x,y...x,y EOF"
 * @return PointSet of the received input points.
 */
PointSet* getInput()
{
    PointSet *ps = new PointSet{};
    long x,y;
    char delim;
    while(!std::cin.eof() && std::cin >> x >> delim >> y)
    {
        ps->add(Point{x,y});
    }
    return ps;
}

/**
 * Swaps two points pointers
 * @param a first point
 * @param b second point
 */
void swapPoints(Point *a, Point *b)
{
    Point c = *a;
    *a = *b;
    *b = c;
}

/**
 * Finds the minimum point for the Convex Hull. The
 * @param arr
 * @param size
 * @return
 */
Point* findMin(Point* arr, const int size)
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

/**
 * Three points are a counter-clockwise turn if ccw > 0, clockwise if
 * ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 * gives twice the signed  area of the triangle formed by p1, p2 and p3.
 */
long ccw(const Point &p1,const  Point &p2,const  Point &p3)
 {
    return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY()) - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
}



double angle(Point &p)
{
    long deltaX = minPoint.getX() - p.getX();
    long deltaY = minPoint.getY() - p.getY();
    return atan2(deltaY, deltaX);

}

bool angleCompare(Point &p1, Point &p2)
{
    long deltaX1 = minPoint.getX() - p1.getX();
    long deltaX2 = minPoint.getX() - p2.getX();
    long deltaY1 = minPoint.getY() - p1.getY();
    long deltaY2 = minPoint.getY() - p2.getY();

    if ((deltaY1 == 0) && (deltaY2 == 0))
    {
        return p1.getX() < p2.getX();
    }

    if ((deltaY1 == 0) || (deltaY2 == 0))
    {
        return deltaY1 == 0;
    }
    if ((deltaX1 == 0) && (deltaX2 == 0))
    {
        return p1.getY() < p2.getY();
    }
    return angle(p1) < angle(p2);
}

/**
 * Removes duplicates angles from a sorted array.
 * @param points array of points
 * @param size size of the array
 * @return new size of the array.
 */
int removeDuplicateAngles(Point* points, int size)
{
    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int n = 1; // Initialize size of modified array
    for (int i = 2; i < size; ++i)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < size && angle(points[i]) == angle(points[i + 1]))
        {
            i++;
        }
        n++;  // Update size of modified array
        points[n] = points[i];
        if(i == size - 1)
        {
            i++;
            n++;
            points[n] = points[i];
        }
    }
    return n;
}

PointSet* createSetFromArray(Point* points, int size)
{
    PointSet* ret = new PointSet;
    for (int j = 1; j <= size ; ++j) {
        ret->add(points[j]);
    }
    delete[] points;
    return ret;
}

/**
 * Graham Scan algorithm from Wikipedia.
 * @param set set to create Convex Hull of
 * @return a Convex Hull set of the given set.
 */
PointSet* createConvexHull(PointSet& set)
{

    int size = set.size();
    if (size <= MIN_CONVEX_HULL_SIZE)
    {
        return &set;
    }
    Point* points = set.toArrayWithPadding(1);
    swapPoints(&points[1], findMin(points, size));
    minPoint = points[1];
    if(size > MIN_CONVEX_HULL_SIZE)
    {
        std::sort(points + 2, points + size + 1, angleCompare);
    }
    points[0] = points[size];
    size = removeDuplicateAngles(points, size);
    if(size <= MIN_CONVEX_HULL_SIZE)
    {
        return createSetFromArray(points, size);
    }
    /* algorithm from wikipedia */
    int m = 1;
    for (int i = 2; i <= size ; ++i)
    {
        while(ccw (points[m-1], points[m], points[i]) <= 0)
        {
            if (m > 1)
            {
                m-= 1;
                continue;
            }
            else if (i == size)
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
    return createSetFromArray(points, m);
}

int main()
{
    PointSet* set = getInput();
    if (set->size() > 0)
    {
        PointSet* convex = createConvexHull(*set);

        std::cout << " " << std::endl;
        std::cout << convex->toString();
        delete convex;
    }
    else
    {
        std::cout << "No input" << std::endl;
    }
    delete set;
}
