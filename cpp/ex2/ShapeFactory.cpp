//
// Created by liron on 9/7/17.
//

#include "ShapeFactory.h"


Shape *ShapeFactory::createShape(char shapeType, std::vector<Point> points)
{
    //TODO: shared_ptr
    switch (shapeType)
    {
        case TRIANGLE:
            Shape s = Triangle{points};
            if (s.isValid())
            {
                return &s; // TODO: this is bad. use shared ptr
            }

            break;
        case TRAPEZOID:
            Shape s = Trapezoid{points};
            if (s.isValid())
            {
                return &s;
            }
        default:
            return nullptr;
    }

    return nullptr;
}
