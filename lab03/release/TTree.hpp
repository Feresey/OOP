#ifndef TTREE_H
#define TTREE_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"
#include <iostream>
#include <memory>

template <class T>
class TTree {
    struct TNode {
        std::shared_ptr<T> value;
        Node* left;
        Node* right;
        Node(T* val, Node* l = nullptr, Node* r = nullptr)
            : value(val)
            , left(l)
            , right(r)
        {
        }
    };

public:
    TTree();
    virtual ~TTree();

    std::shared_ptr<T> getValue(char* path, pTree curr);

    void add(T* triangle);
    void Remove();

    pTree getItem(char* path, pTree curr);
    bool empty();
    void stream(std::ostream& os, const TTree& node, int height) const;
    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);
};

#include "TTree.h"

#endif // TTREE_H
