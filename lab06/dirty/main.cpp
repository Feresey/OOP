#include "TTree.hpp"
#include <iostream>

#define line std::cout << "————————————————————————————————————————————" << std::endl
//\
+ t 1 2 2 + r 2 4 + s 2 + t 1 1 1 + s 3 + r 2 1 + r 1 2

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::shared_ptr<TTree<Figure>> node(new TTree<Figure>());
    char choice;
    char path[200];

    std::cout << "Usage:\n"
              << "\t Add element:   \t + side_a side_b side_c\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n\n";

    std::cout << "command>> ";
    while (std::cin.get(choice)) {
        switch (choice) {
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 't':
                node->add(new Triangle(std::cin), node);
                break;
            case 'r':
                node->add(new Rectangle(std::cin), node);
                break;
            case 's':
                node->add(new Sqr(std::cin), node);
                break;
            }
            break;
        }
        case '-': {
            std::cin.getline(path, 200);
            node->Remove(node->getItem(path, node));
            break;
        }

        case 'g': {
            std::cin.getline(path, 200);
            if (!node->empty()) {

                std::cout << "————————————————————————————————————————————" << std::endl;
                std::weak_ptr<Figure> temp = node->getValue(path, node);
                temp.lock()->Print();
                std::cout << "\tSquare = " << temp.lock()->Square() << std::endl;
                goto end;
            }
            goto end;
        }
        case 's': {
            std::cout << "Show:" << '\n';
            for (auto i : *node) {
                std::cout << *i;
                std::cout << "->";
            }
            std::cout << "nullptr\n";
            goto end;
        }
        default:
            continue;
        }
        std::cout << "————————————————————————————————————————————" << std::endl;
        if (node && !node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
    end:
        std::cout << "command>> ";
    }

    return 0;
}
