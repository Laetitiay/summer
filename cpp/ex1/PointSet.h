#ifndef POINTSET_H
#define POINTSET_H

#include <string>
#include "Point.h"

#define STARTING_CAPACITY 2
#define ARRAY_MULTIPLYER 2
#define NOT_FOUND -1
#define LAST_INDEX (array_size - 1)


/**
 * A class repersenting a set of points.
 */
class PointSet
{

public:
/**
 * Constracts a new PointSet of size 0 and capacity 2
 * @return an empty Point Set
 */
    PointSet();

/**
 * Constracts a new PointSet from an existing Point Set
 * @return a copy of the given PointSet
 */
    PointSet(const PointSet &pv);

/**
 * Deconstructs a point set.
 */
    ~PointSet();

/**
 * Creats a string representation of the PointSet in the form of (x1,y1)\n...(x_n,y_n)\n
 * @return a string representation of the set.
 */
    const std::string toString() const;

/**
 * Adds a point to the point set.
 * @param p point to add
 * @return true iff the point was added to the set.
 */
    bool add(const Point &toAdd);

/**
 * Removes a point from the set.
 * @param p point to remove
 * @return true iff the point was removed from the set.
 */
    bool remove(const Point &toRemove);

/**
 * How many points are in the set.
 * @return the size of the set.
 */
    int size() const;

/**
 * Check if a point exists in the set.
 * @param p point to check existence of
 * @return The index of it if it does, -1 otherwise.
 */
    int member(const Point &p) const;

/**
 * Equal operator. Two sets are equal iff they have exactly the same points.
 * @param rhs other set to compare to
 * @return true iff the sets are equal
 */
    bool operator==(PointSet &rhs);

/**
 * Unequal operator. Two sets are unequal iff one set has at least one point the other one doesn't.
 * @param rhs other set to compare to
 * @return true iff the sets are equal
 */
    bool operator!=(PointSet &rhs);

/**
 * and operator. creates a set that has points that both sets have.
 * @param rhs other set to operate with
 * @return PointSet that has all the points that both sets have.
 */
    PointSet &operator&(const PointSet &rhs);

/**
 * Hasama operator. Creates a copy of the set into another set.
 * @param rhs set to copy
 * @return a new set.
 */
    PointSet operator=(const PointSet &rhs);

/**
 * minus operator. creates a set from the lhs set that doesn't have the points the rhs does.
 * @param rhs other set to remove points that it has
 * @return PointSet that has all the points of a that are not in b.
 */
    PointSet &operator-(const PointSet &set);

/**
 * Cerates an array from the set with padding at the beginning
 * @param padding how many padding would you like
 * @return a padded array of the set
 */
    Point *toArrayWithPadding(int padding);

private:
    Point *values;
    int capacity;
    int array_size;

/**
 * Increases the size of the array of the set by a factor of ARRAY_MULTIPLYER.
 */
    void _increaseArraySize();

};


#endif
