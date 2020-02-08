#ifndef TREE_H
#define TREE_H

#include "TIterator.hpp"
#include "TTree.hpp"

template <class T>
class Tree {
private:
    pTree root;

public:
    Tree();
    ~Tree();

    Iter<TTree<T>, T> begin();
    Iter<TTree<T>, T> end();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const Tree<B>& node);
    void Remove(char* path);
    void add(Figure* triangle);
    pTree get(char* path);
    pTree get() { return get("\0"); }
    std::shared_ptr<T> getItem(char* path);
    bool empty();
};

#include "Tree.h"
#endif // !TREE_H