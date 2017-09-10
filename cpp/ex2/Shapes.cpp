#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>
#include "Defs.h"
#include "Point.h"
#include "Shape.h"
#include "ShapeFactory.h"
#include "PrintOuts.h"

#define MINIMUM_NUM_ARGS 2
#define EXPECTED_NUM_ARGS 3
#define MSG_INCORRECT_ARGC "Incorrect amount of arguments"
#define MSG_ILLEGAL_SHAPE "You have an illegal shape. Aborting."
#define IO_ERROR -1
#define PRECISION_RATE 2

std::vector<Shape *> *getInput(std::string fileName)
{
    std::vector<Shape *> *shapes = new std::vector<Shape *>;

    char shapeType;
    CordType x;
    CordType y;
    Shape *s;

    std::streambuf *originalCin = std::cin.rdbuf();
    std::ifstream inputFile(fileName);
    std::cin.rdbuf(inputFile.rdbuf());


    while (!std::cin.eof() && std::cin >> shapeType)
    {
        std::vector<Point> points;
        while (std::cin.peek() != '\n' && !std::cin.eof())
        {
            std::cin >> x;
            std::cin >> y;
            points.push_back(Point{x, y});
        }
        s = ShapeFactory::createShape(shapeType, points);
        if (s == nullptr)
        {
            return nullptr;
        }
        shapes->push_back(s);
    }

    std::cin.rdbuf(originalCin);
    inputFile.close();
    return shapes;
}

bool vectorHasIntersections(std::vector<Shape *> *shapes)
{
    for (int i = 0; i < shapes->size() - 1; ++i)
    {
        for (int j = i + 1; j < shapes->size(); ++j)
        {
            if ((*shapes)[i]->contains(*(*shapes)[j]) || (*shapes)[i]->hasIntersection(*(*shapes)[j]))
            {
                (*shapes)[i]->print();
                (*shapes)[j]->print();
                reportDrawIntersect();
                return true;
            }
        }
    }
    return false;
}

double getShapesArea(std::vector<Shape *> *shapes)
{
    double sum = 0;
    for (const auto &shape :(*shapes))
    {
        sum += shape->calculateArea();

    }
    return sum;
}

int main(int argc, char *argv[])
{

    std::streambuf *originalCout = nullptr;
    std::ofstream outputFile;
    std::cout.precision(PRECISION_RATE);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);

    if (argc < MINIMUM_NUM_ARGS || argc > EXPECTED_NUM_ARGS)
    {
        std::cerr << MSG_INCORRECT_ARGC << std::endl;
        return IO_ERROR;
    }

    std::vector<Shape *> *shapes = getInput(argv[1]);
    if (shapes == nullptr)
    {
        std::cerr << MSG_ILLEGAL_SHAPE << std::endl;
        return IO_ERROR;
    }

    if (argc == EXPECTED_NUM_ARGS)
    {
        originalCout = std::cout.rdbuf();
        outputFile = std::ofstream{argv[2]};
        std::cout.rdbuf(outputFile.rdbuf());
    }

    if (!vectorHasIntersections(shapes))
    {
        printArea(getShapesArea(shapes));
    }

    if (argc == EXPECTED_NUM_ARGS)
    {
        std::cout.rdbuf(originalCout);
        outputFile.close();
    }


    /*
     * TODO: write to file.
     */
    return 0;
}