#include <iostream>
#include "Tree.hpp"

int main()
{
    std::shared_ptr<Tree<Figure>> node(new Tree<Figure>());
    char inp;
    char path[100];

    std::cout << "Usage:\n"
              << "\t Add element:   \t + side_a side_b side_c\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n\n";

    std::cout << "command>> ";
    while (std::cin.get(inp))
    {
        if (inp == '\n')
            continue;
        if (inp == '+')
        {
            std::cin >> inp;
            if (inp == 't')
                node->add(new Triangle(std::cin));
            if (inp == 'r')
                node->add(new Rectangle(std::cin));
            if (inp == 's')
                node->add(new Sqr(std::cin));
        }
        else if (inp == '-')
        {
            std::cin >> path;
            node->Remove(path);
        }
        else if (inp == 'g')
        {
            if (!node->empty())
            {
                std::cin >> path;
                std::cout << "______________________________________________" << std::endl;
                node->getItem(path)->Show(std::cout);
                std::cout << "\tSquare = " << node->getItem(path)->Square() << std::endl;
                goto loop;
            }
            // continue;
        }
    loop:
        std::cout << "________________________________________________" << std::endl;
        
        if (node && !node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
        std::cout << "command>> ";
    }

    return 0;
}
