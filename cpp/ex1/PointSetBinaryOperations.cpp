#include <iostream>
#include "PointSet.h"

void showOffNotEqual()
{
    Point p1{1,1};
    Point p2{2,2};
    Point p3{3,3};
    PointSet a{};
    PointSet b{};
    a.add(p1);
    a.add(p2);
    a.add(p3);
    b.add(p1);
    b.add(p2);
    std::cout << "Set a:" << std::endl << a.toString();
    std::cout << "Set b:" << std::endl << b.toString();
    std::cout << "a != b ?????" << std::endl;
    std::string msg;
    if( a != b)
    {
        msg = "true!\n";
    }
    else
    {
        msg = "false!\n";
    }
    std::cout << msg << std::endl;

}

void showOffEqual()
{
    Point p1{1,1};
    Point p2{2,2};
    Point p3{3,3};
    PointSet a{};
    PointSet b{};
    a.add(p1);
    a.add(p2);
    a.add(p3);
    b.add(p1);
    b.add(p2);
    b.add(p3);
    std::cout << "Set a:" << std::endl << a.toString();
    std::cout << "Set b:" << std::endl << b.toString();
    std::cout << "a == b ?????" << std::endl;
    std::string msg;
    if( a == b)
    {
        msg = "true!\n";
    }
    else
    {
        msg = "false!\n";
    }
    std::cout << msg << std::endl;
}

void showOffMinus()
{
    Point p1{1,1};
    Point p2{2,2};
    Point p3{3,3};
    PointSet a{};
    PointSet b{};
    a.add(p1);
    a.add(p2);
    a.add(p3);
    b.add(p1);
    b.add(p2);
    std::cout << "Set a:" << std::endl << a.toString();
    std::cout << "Set b:" << std::endl << b.toString();
    std::cout << "a \\ b ?????" << std::endl;
    std::cout << (a-b).toString() << std::endl;

}

void showOffAnd()
{
    Point p1{1,1};
    Point p2{2,2};
    Point p3{3,3};
    PointSet a{};
    PointSet b{};
    a.add(p1);
    a.add(p2);
    a.add(p3);
    b.add(p1);
    b.add(p2);
    std::cout << "Set a:" << std::endl << a.toString();
    std::cout << "Set b:" << std::endl << b.toString();
    std::cout << "a & b ?????" << std::endl;
    std::cout << (a & b).toString() << std::endl;
}

void showOffHasama()
{
    Point p1{1,1};
    Point p2{2,2};
    Point p3{3,3};
    PointSet a{};
    PointSet b{};
    a.add(p1);
    a.add(p2);
    a.add(p3);
    b.add(p1);
    b.add(p2);
    std::cout << "Set a:" << std::endl << a.toString();
    std::cout << "Set b:" << std::endl << b.toString();
    std::cout << "a = b makes a be ??????" << std::endl;
    std::cout << (a = b).toString() << std::endl;

}



int main()
{

    std::cout << "Showing off operators:" << std::endl;
    showOffNotEqual();
    showOffEqual();
    showOffMinus();
    showOffAnd();
    showOffHasama();
    return 0;
}
