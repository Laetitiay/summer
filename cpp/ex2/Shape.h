#include <vector>
#include "Point.h"
#include "Defs.h"
#include "PrintOuts.h"
//
// Created by liron on 9/5/17.
//

#ifndef EX2_SHAPE_H
#define EX2_SHAPE_H
#define AREA_MODIFIER 2.0


class Shape
{

public:
    Shape(std::vector<Point> points, std::string name);

    static double threePointsCalc(Point &p1, Point &p2, Point &p3);

    bool contains(Shape &);

    bool hasIntersection(Shape &);

    unsigned long size();

    virtual bool isValid() = 0;

    virtual double calculateArea() = 0;

    virtual void print() = 0;


protected:
    std::vector<Point> points;
    const std::string data_member;
private:

};


#endif //EX2_SHAPE_H
