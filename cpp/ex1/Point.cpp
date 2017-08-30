#include <algorithm>
#include <iostream>
#include "Point.h"

// constructor of point
Point::Point(long int x, long int y)
{
    set(x,y);
}

void Point::set(long x, long y)
{
    _x = x;
    _y = y;
}


std::string Point::toString()const
{
    return "(" + std::to_string(_x) + "," + std::to_string(_y) + ")";
}

bool Point::operator==(const Point &rhs)const
{
    return _x == rhs._x && _y == rhs._y;
}

//int main(){
//    int c[] = {543,34,2,3,5};
//    for (auto i : c){
//        std::cout << i << ", ";
//    }
//    std::cout << std::endl;
//    std::sort(std::begin(c), std::end(c));
//    for (auto i : c){
//        std::cout << i << ", ";
//    }
//}