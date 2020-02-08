// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <iostream>

#include "Tree.hpp"

#define line std::cout << "____________________________________________" << std::endl

//!test!\\
+ t 1 2 2 + r 2 4 + s 2 + t 1 1 1 + s 3 + r 2 1 + r 1 2

//!test!\\
+s 2 +r 2 2 +s 2 c t 2

int main()
{
    std::shared_ptr<Tree<Queue<Figure>, Figure>> node(new Tree<Queue<Figure>, Figure>());
    char choice;
    char path[200];
    int type;

    std::cout << "Usage:\n"
              << "\t Add element:   \t + {elem_type} {sides}\n"
              << "\t Delete element:\t - path \n"
              << "\t\t path={r,l}*\n"
              << "\t Delete by criteria: c\n"
              << "\t\t and select avaliable criteria\n"
              << "\t Get element:   \t g path\n"
              << "\t\t path={r,l}*\n"
              << "\t Show container:\t s\n\n";

    std::cout << "command>> ";
    while (std::cin.get(choice)) {
        switch (choice) {
        case '+': {
            std::cin >> choice;
            switch (choice) {
            case 't':
                node->add(new Triangle(std::cin));
                break;
            case 'r':
                node->add(new Rectangle(std::cin));
                break;
            case 's':
                node->add(new Sqr(std::cin));
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
                auto temp = node->get(path)->value;
                temp->Print(std::cout);
                std::cout << "\tSquare = " << temp->Square() << std::endl;
            }
            goto end;
        }
        case 'c': {
            std::cout << "To remove by type press t\n"
                      << "To remove by value press v\n"
                      << "Your choice: ";
        rem:
            std::cin >> choice;
            switch (choice) {
            case 't':
                std::cout << "Enter fig type (0 = triangle, 1 = square, 2 = rectangle): ";
                std::cin >> type;
                if (!node->empty())
                    node->Remove(static_cast<fig>(type));
                break;
            case 'v':
                std::cout << "Enter remove value(double): ";
                double s;
                std::cin >> s;
                if (!node->empty())
                    node->Remove(s);
                break;
            default:
                std::cout << "Incorrect choice, try again:";
                goto rem;
            }
            break;
        }

        case 's': {
            std::cout << "Show:" << '\n';
            for (auto i : *node) {
                i->Print(std::cout);
                std::cout << "->";
            }
            std::cout << "nullptr\n";
            goto end;
        }
        default:
            continue;
        }
        line;
        if (!node->empty())
            std::cout << *node;
        else
            std::cout << "empty!\n";
    end:
        std::cout << "command>> ";
    }

    return 0;
}
