#ifndef EX2_SHAPEFACTORY_H
#define EX2_SHAPEFACTORY_H


#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"

#define TRAPEZOID 't'
#define TRIANGLE 'T'


/**
 * A factory of shapes.
 */
class ShapeFactory
{

public:
    /**
     * Creates a shape of the given type and points.
     * @param shapeType type of shape
     * @param points points vector
     * @return a shape if it is valid, nullptr otherwise.
     */
    static Shape *createShape(char shapeType, std::vector<Point> points);
};


#endif //EX2_SHAPEFACTORY_H
