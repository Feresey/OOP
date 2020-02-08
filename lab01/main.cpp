#include <cstdlib>
#include <iostream>

#include "TTree.hpp"
// #include "Triangle.hpp"

int main()
{
    TTree node;
    char inp;
    char path[10];
    std::cout << "Usage:\n"
              << "\t Add element:   \t + side_a side_b side_c\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n\n";

    std::cout << "command>> ";
    while (std::cin.get(inp)) {

        if (inp == '\n')
            continue;
        if (inp == '+') {
            node.add(new Triangle(std::cin));
        } else if (inp == '-') {
            std::cin >> path;
            node.Remove(node.get(path));
        } else if (inp == 'g') {
            std::cin >> path;
            std::cout << "______________________________________________" << std::endl;
            std::cout << node.getItem(path) << "\tSquare = " 
            << node.getItem(path)->Square() << std::endl;
            std::cout << "______________________________________________" << std::endl;

            continue;
        }
        std::cout << "______________________________________________" << std::endl;
        std::cout << node;
        std::cout << "command>> ";
    }

    return 0;
}
