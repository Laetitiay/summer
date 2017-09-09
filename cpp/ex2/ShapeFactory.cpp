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
        //std::shared_ptr<Shape> s;
        case TRIANGLE:
            //s = std::shared_ptr<Triangle{points}>;
            s = new Triangle{points};
            if (s->isValid())
            {
                return s; // TODO: this is bad. use shared ptr
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
