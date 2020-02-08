#include "Tree.hpp"
#include <iostream>

#define line std::cout << "————————————————————————————————————————————" << std::endl
// + t 1 2 2 + r 2 4 + s 2 + t 1 1 1 + s 3 + r 2 1 + r 1 2

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
    while (std::cin >> inp) {

        if (inp == '\n')
            continue;
        if (inp == '+') {
            std::cin >> inp;
            if (inp == 't')
                node->add(new Triangle(std::cin));
            if (inp == 'r')
                node->add(new Rectangle(std::cin));
            if (inp == 's')
                node->add(new Sqr(std::cin));
        } else if (inp == '-') {
            std::cin >> path;
            path[99] = '\0';
            node->Remove(path);
        } else if (inp == 'g') {
            std::cin >> path;
            line;
            std::weak_ptr<Figure> temp = node->getItem(path);
            if (!temp.lock() || temp.lock()->empty())
                goto end;
            temp.lock()->Print();
            std::cout << "\tSquare = " << node->getItem(path)->Square() << std::endl;
            line;
            goto end;
        }
        line;
        if (node && !node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
    end:
        std::cout << "command>> ";
    }

    return 0;
}
