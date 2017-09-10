//
// Created by liron on 9/7/17.
//

#include <memory>
#include "ShapeFactory.h"


/**
 * Creates a shape of the given type and points.
 * @param shapeType type of shape
 * @param points points vector
 * @return a shape if it is valid, nullptr otherwise.
 */
Shape *ShapeFactory::createShape(char shapeType, std::vector<Point> points)
{
    Shape *s;
    //TODO: shared_ptr
    switch (shapeType)
    {
        case TRIANGLE:
            s = new Triangle{points};
            break;
        case TRAPEZOID:
            s = new Trapezoid{points};
            break;
        default:
            return nullptr;
    }

    if (s->isValid())
    {
        return s;
    }
    delete s;
    return nullptr;
}
