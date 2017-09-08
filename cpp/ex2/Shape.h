#include <vector>
#include "Point.h"
//
// Created by liron on 9/5/17.
//

#ifndef EX2_SHAPE_H
#define EX2_SHAPE_H


class Shape
{

public:
    Shape(std::vector<Point> points);
    static double threePointsCalc(Point p1, Point p2, Point p3);
    bool contains(const Shape&) const;
    bool hasIntersection(const Shape&) const;

    unsigned long size()const;
    virtual bool isValid() const = 0;
    virtual double calculateArea() const = 0;


protected:
    std::vector<Point> points;
    const std::string data_member;
private:

};


#endif //EX2_SHAPE_H
