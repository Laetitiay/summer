#ifndef POINTSET_H
#define POINTSET_H
#include <string>
#include "Point.h"

class PointSet
{

public:
    PointSet();
    ~PointSet() = default;
    std::string toString()const;
    bool add(const Point &toAdd);
    bool remove(Point &toRemove);
    int size()const;
    bool operator==(const PointSet &rhp)const;
    bool operator!=(const PointSet &rhp)const;
    PointSet operator-(const PointSet &set1, const PointSet &set2);
    PointSet operator&(const PointSet &set1, const PointSet &set2);
    PointSet operator=(const PointSet &rhs);

private:

};

#endif
