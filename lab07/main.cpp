#include "Tree.hpp"
#include <iostream>

#define line std::cout << "____________________________________________" << std::endl

//!test!\\
+ t 1 2 2 + r 2 4 + s 2 + t 1 1 1 + s 3 + r 2 1 + r 1 2

int main()
{
    std::shared_ptr<Tree<Figure>> node(new Tree<Figure>());
    char choice;
    char path[200];

    std::cout << "Usage:\n"
              << "\t Add element:   \t + {elem_type} {sides}\n"
              << "\t Delete element:\t - path \n"
              << "\t\t\t\t path={r,l}*\n"
              << "\t Get element:   \t g path\n"
              << "\t\t\t\t path={r,l}*\n"
              << "\t Show container:\t s\n\n"
              << "\t Sort container:\t %\n\n";

    std::cout << "command>> ";
    while (std::cin.get(choice)) {
        switch (choice) {
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 't':
                node->add(std::shared_ptr<Figure>(new Triangle(std::cin)));
                break;
            case 'r':
                node->add(std::shared_ptr<Figure>(new Rectangle(std::cin)));
                break;
            case 's':
                node->add(std::shared_ptr<Figure>(new Sqr(std::cin)));
                break;
            }
            break;
        }
        case '-': {
            std::cin.getline(path, 200);
            node->Remove(path);
            break;
        }

        case 'g': {
            std::cin.getline(path, 200);
            if (!node->empty()) {

                line;
                std::weak_ptr<Figure> temp = node->getItem(path);
                temp.lock()->Print(std::cout);
                std::cout << "\tSquare = " << temp.lock()->Square() << std::endl;
                goto end;
            }
            goto end;
        }
        case 's': {
            std::cout << "Show:\n";
            for (auto i : *node) {
                i->Print(std::cout);
                std::cout << "->";
            }
            std::cout << "nullptr\n";
            goto end;
        }
        case '%': {
            std::cout << "Sort:\n"
                      << "Usual sort:\tu\n"
                      << "Parallel sort:\tp\n";
            std::cin >> choice;
            node->Sort(choice);
            for (auto i : *node) {
                std::cout << i->Square();
                std::cout << ' ';
            }
            std::cout << '\n';
            goto wrt;
        }
        default:
            continue;
        }
    wrt:
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
