#ifndef POINTSET_H
#define POINTSET_H
#include <string>
#include "Point.h"
#define STARTING_CAPACITY 2
#define ARRAY_MULTIPLYER 2
#define NOT_FOUND -1
#define LAST_INDEX (array_size - 1)


class PointSet
{

public:
    PointSet();
    PointSet(const PointSet &pv);
    ~PointSet();
    std::string toString()const;
    bool add(const Point &toAdd);
    bool remove(Point &toRemove);
    int size()const;
    int member(const Point &p)const;
    bool operator==(PointSet &rhs);
    bool operator!=(PointSet &rhs);
    PointSet &operator&(const PointSet &rhs);
    PointSet operator=(const PointSet &rhs);
    PointSet & operator-(PointSet &set);
    Point *toArrayWithPadding(int padding);

private:
    Point *values;
    int capacity;
    int array_size;
    void increaseArraySize();

};


#endif
