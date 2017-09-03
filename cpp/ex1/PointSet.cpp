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
    if (member(p) >= 0)
    {
        return false;
    }

    if (array_size == capacity)
    {
        _increaseArraySize();
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
    if (index == NOT_FOUND)
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
int PointSet::member(const Point &p) const
{
    for (int i = 0; i < array_size; ++i)
    {
        if (values[i] == p)
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
int PointSet::size() const
{
    return array_size;
}

/**
 * Equal operator. Two sets are equal iff they have exactly the same points.
 * @param rhs other set to compare to
 * @return true iff the sets are equal
 */
bool PointSet::operator==(PointSet &rhs)
{
    if (array_size != rhs.array_size)
    {
        return false;
    }
    std::sort(values, values + array_size, Point::naturalCompare);
    std::sort(rhs.values, rhs.values + array_size, Point::naturalCompare);
    for (int i = 0; i < array_size; ++i)
    {
        if (values[i] != rhs.values[i])
        {
            return false;
        }
    }
    return true;
}


/**
 * Unequal operator. Two sets are unequal iff one set has at least one point the other one doesn't.
 * @param rhs other set to compare to
 * @return true iff the sets are equal
 */
bool PointSet::operator!=(PointSet &rhs)
{
    return !(operator==(rhs));
}

/**
 * minus operator. creates a set from the lhs set that doesn't have the points the rhs does.
 * @param rhs other set to remove points that it has
 * @return PointSet that has all the points of a that are not in b.
 */
PointSet &PointSet::operator-(const PointSet &rhs)
{
    PointSet *ret = new PointSet{};
    for (int i = 0; i < array_size; ++i)
    {
        if (rhs.member(values[i]) == NOT_FOUND)
        {
            ret->add(values[i]);
        }
    }
    return *ret;
}

/**
 * and operator. creates a set that has points that both sets have.
 * @param rhs other set to operate with
 * @return PointSet that has all the points that both sets have.
 */
PointSet &PointSet::operator&(const PointSet &rhs)
{
    PointSet *ret = new PointSet{};
    for (int i = 0; i < array_size; ++i)
    {
        if (rhs.member(values[i]) != NOT_FOUND)
        {
            ret->add(values[i]);
        }
    }
    return *ret;
}

/**
 * Assignment operator. Creates a copy of the set into another set.
 * @param rhs set to copy
 * @return a new set.
 */
PointSet PointSet::operator=(const PointSet &rhs)
{
    if (&rhs == this)
    {
        return *this;
    }
    return PointSet(rhs);
}

/**
 * Creats a string representation of the PointSet in the form of (x1,y1)\n...(x_n,y_n)\n
 * @return a string representation of the set.
 */
std::string PointSet::toString() const
{
    std::sort(values, values + array_size, Point::naturalCompare);
    std::string ret = "";
    for (int i = 0; i < array_size; ++i)
    {
        ret += values[i].toString() + "\n";
    }
    return ret;
}

/**
 * Cerates an array from the set with padding at the beginning
 * @param padding how many padding would you like
 * @return a padded array of the set
 */
Point *PointSet::toArrayWithPadding(int padding = 1)
{
    Point *retArray = new Point[array_size + padding];
    //std::copy(values, values + capacity, retArray + padding);
    for (int i = padding; i < array_size + padding; ++i)
    {
        retArray[i] = values[i - 1];
    }
    return retArray;
}

// private methods //

/**
 * Increases the size of the array of the set by a factor of ARRAY_MULTIPLYER.
 */
void PointSet::_increaseArraySize()
{
    Point *tempArray = new Point[capacity * ARRAY_MULTIPLYER];
    std::copy(values, values + array_size, tempArray);
    delete[] values;
    capacity *= ARRAY_MULTIPLYER;
    values = tempArray;
}


