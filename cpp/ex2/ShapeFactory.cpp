//
// Created by liron on 9/7/17.
//

#include <memory>
#include "ShapeFactory.h"


Shape *ShapeFactory::createShape(char shapeType, std::vector<Point> points)
{
    //TODO: shared_ptr
    switch (shapeType)
    {
//        std::shared_ptr<Shape> s;
//        case TRIANGLE:
//            s = std::shared_ptr<Triangle{points}>;
//            if (s.isValid())
//            {
//                return &s; // TODO: this is bad. use shared ptr
//            }
//
//            break;
//        case TRAPEZOID:
//            s = Trapezoid{points};
//            if (s.isValid())
//            {
//                return &s;
//            }
        default:
            return nullptr;
    }

    return nullptr;
}
