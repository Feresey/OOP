#include <cstdlib>
#include "Triangle.hpp"
#include "Sqr.hpp"
#include "Rectangle.hpp"

int main()
{
    std::cout << "Create Triangle:" << std::endl
              << "Insert a, b, c >> ";
    Figure *triangle = new Triangle(std::cin);
    triangle->Print();
    std::cout << "Square = " << triangle->Square() << std::endl
              << std::endl;

    std::cout << "Create Square:" << std::endl
              << "Insert a >> ";
    Sqr *square = new Sqr(std::cin);
    square->Print();
    std::cout << "Square = " << square->Square() << std::endl
              << std::endl;

    std::cout << "Create Rectangle:" << std::endl
              << "Insert a, b >> ";
    Rectangle *rectangle = new Rectangle(std::cin);
    rectangle->Print();
    std::cout << "Square = " << rectangle->Square() << std::endl
              << std::endl;

    delete triangle;
    delete square;
    delete rectangle;

    return 0;
}
