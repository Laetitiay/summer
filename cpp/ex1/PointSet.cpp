#include <iostream>
#include <algorithm>
#include "PointSet.h"

/**
 * Constracts a new PointSet of size 0 and capacity 2
 * @return an empty Point Set
 */
PointSet::PointSet()
{
    capacity = STARTING_CAPACITY;
    array_size = 0;
    values = new Point[capacity];
}

/**
 * Constracts a new PointSet from an existing Point Set
 * @return a copy of the given PointSet
 */
PointSet::PointSet(const PointSet &pv)
{
    capacity = pv.capacity;
    array_size = pv.array_size;
    values = new Point[capacity];
    std::copy(pv.values, pv.values + pv.size(), values);
}

/**
 * Deconstructs a point set.
 */
PointSet::~PointSet()
{
    delete[] values;
}

/**
 * Adds a point to the point set.
 * @param p point to add
 * @return true iff the point was added to the set.
 */
bool PointSet::add(const Point &p)
{
    if(member(p) >= 0)
    {
        return false;
    }

    if(array_size == capacity)
    {
        increaseArraySize();
    }

    values[array_size] = p;
    array_size++;

    return true;
}

/**
 * Removes a point from the set.
 * @param p point to remove
 * @return true iff the point was removed from the set.
 */
bool PointSet::remove(Point &p)
{
    int index = member(p);
    if(index == NOT_FOUND)
    {
        return false;
    }

    values[index] = values[LAST_INDEX];
    return true;
}


/**
 * Check if a point exists in the set.
 * @param p point to check existence of
 * @return The index of it if it does, -1 otherwise.
 */
int PointSet::member(const Point &p)const
{
    for (int i = 0; i < array_size ; ++i) {
        if(values[i] == p)
        {
            return i;
        }
    }
    return NOT_FOUND;
}

/**
 * How many points are in the set.
 * @return the size of the set.
 */
int PointSet::size() const {
    return array_size;
}

bool PointSet::operator==(PointSet &rhs)
{
    if(array_size != rhs.array_size)
    {
        return false;
    }
    std::sort(values, values + array_size, Point::naturalCompare);
    std::sort(rhs.values, rhs.values + array_size, Point::naturalCompare);
    for (int i = 0; i < array_size; ++i) {
        if(values[i] != rhs.values[i])
        {
            return false;
        }
    }
    return true;
}


bool PointSet::operator!=(PointSet &rhs)
{
    return !(operator==(rhs));
}

PointSet PointSet::operator-(PointSet &rhs)
{
    //TODO: IMPROVE THIS - if not, make const.
    PointSet ret{};
//    std::sort(values, values + array_size, Point::naturalCompare);
//    std::sort(rhs.values, rhs.values + array_size, Point::naturalCompare);
    for (int i = 0; i < array_size; ++i)
    {
        if(rhs.member(values[i]) == NOT_FOUND)
        {
            ret.add(values[i]); // TODO: does it create a copy:
        }
    }
    return ret;
}

PointSet PointSet::operator&(const PointSet &rhs) {
    //TODO: IMPROVE THIS
    PointSet ret{};
//    std::sort(values, values + array_size, Point::naturalCompare);
//    std::sort(rhs.values, rhs.values + array_size, Point::naturalCompare);
    for (int i = 0; i < array_size; ++i)
    {
        if(rhs.member(values[i]) != NOT_FOUND)
        {
            ret.add(values[i]); // TODO: does it create a copy:
        }
    }
    return ret;
}

PointSet PointSet::operator=(const PointSet &rhs) {
    return PointSet(rhs);
}


std::string PointSet::toString() const {
    std::sort(values, values + array_size, Point::naturalCompare);
    std::string ret = "";
    for (int i = 0; i < array_size; ++i)
    {
        ret += values[i].toString() + "\n";
    }
    return ret;
}

// private methods //
void PointSet::increaseArraySize()
{
    Point *tempArray = new Point[capacity * ARRAY_MULTIPLYER];
    std::copy(values, values + capacity, tempArray);
    delete[] values;
    capacity *= ARRAY_MULTIPLYER;
    values = tempArray;
}


//int main()
//{
//    // testing
//    Point p1{17,2};
//    Point p2{4,2};
//    Point p3{5,3};
//    Point p4{17,4};
//    Point p5{4,1};
//    PointSet a{};
//    a.add(p4);
//    a.add(p1);
//    a.add(p2);
//    a.add(p3);
//    a.add(p5);
//    PointSet b{};
//    b.add(p1);
//    b.add(p2);
//    b.add(p3);
//    PointSet c = a;
//    a.remove(p4);
//    std::cout << c.toString();
//}
