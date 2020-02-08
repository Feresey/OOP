#ifndef TREE_H
#define TREE_H

#include "TTree.hpp"

class Tree {
private:
    pTree root;

public:
    Tree();
    ~Tree();

    friend std::ostream& operator<<(std::ostream& os, const Tree& node);
    void Remove(char* path);
    void add(Figure* triangle);
    pTree get(char* path);
    pFigure getItem(char* path);
    bool empty();
};

#endif // !TREE_H