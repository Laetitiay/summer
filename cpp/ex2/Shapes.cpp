#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Defs.h"
#include "Point.h"
#include "Shape.h"
#include "ShapeFactory.h"

#define EXPECTED_NUM_ARGS 3
#define MSG_INCORRECT_ARGC "Incorrect amount of arguments"



int main(int argc, char** argv)
{







//    std::vector<std::shared_ptr<Shape>> sha;
//    sha.push_back(std::shared_ptr<Trapezoid>{});
    if (argc != EXPECTED_NUM_ARGS)
    {

        Shape * s;
        std::vector<Point> a;
        a.push_back(Point{-6,5});
        a.push_back(Point{6,-6});
        a.push_back(Point{5,6});
        s = new Triangle{a};
        std::vector<Point> b;
        Shape * t;
        b.push_back(Point{0,0});
        b.push_back(Point{4,0});
        b.push_back(Point{4,4});
        b.push_back(Point{0,4});
        t = new Trapezoid{b};
        std::cout << s->hasIntersection(*t);
        //std::cerr << MSG_INCORRECT_ARGC << std::endl;
        return -1;
    }
    /*
     * TODO: Read file, could not read file, write to file.
     */
    std::vector<Shape*> shapes;

    char shapeType;
    char zevel;
    CordType x;
    CordType y;

    std::streambuf* originalCout = std::cout.rdbuf();
    std::ifstream inputFile(argv[1]);
    std::cin.rdbuf(inputFile.rdbuf());

    while (!std::cin.eof())
    {
        std::cin >> shapeType;
        std::cin >> zevel;
        std::vector<Point> points;
        while(zevel != '\n' && !std::cin.eof())
        {

            std::cin >> x;
            std::cin >> zevel;
            std::cin >> y;
            std::cin >> zevel; // TODO: maybe if eof can't read it
            points.push_back(Point{x,y});
        }
        shapes.push_back(ShapeFactory::createShape(shapeType,points));
    }


    std::cout.rdbuf(originalCout);
    inputFile.close();
    return 0;
}