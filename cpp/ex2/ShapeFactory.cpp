//
// Created by liron on 9/7/17.
//

#include <memory>
#include "ShapeFactory.h"


Shape *ShapeFactory::createShape(char shapeType, std::vector<Point> points)
{
    Shape *s;
    //TODO: shared_ptr
    switch (shapeType)
    {
        case TRIANGLE:
            s = new Triangle{points};
            if (s->isValid())
            {
                return s;
            }
            delete s;
            break;
        case TRAPEZOID:
            s = new Trapezoid{points};
            if (s->isValid())
            {
                return s;
            }
        default:
            return nullptr;
    }

    return nullptr;
}
