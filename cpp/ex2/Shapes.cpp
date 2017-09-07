#include <iostream>
#include <fstream>
#include <vector>
#include "Defs.h"
#include "Point.h"
#include "Shape.h"
#include "ShapeFactory.h"

#define EXPECTED_NUM_ARGS 3
#define MSG_INCORRECT_ARGC "Incorrect amount of arguments"



int main(int argc, char** argv)
{
    if (argc != EXPECTED_NUM_ARGS)
    {

        std::cerr << MSG_INCORRECT_ARGC << std::endl;
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
    static std::ifstream inputFile(argv[1]);
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