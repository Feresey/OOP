#ifndef TTREE_H
#define TTREE_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "TAllocationBlock.hpp"
#include "TIterator.hpp"
#include "Triangle.hpp"

#define pTree std::shared_ptr<TTree<T>>
#define wTree std::weak_ptr<TTree<T>>

template <class T>
class TTree {
public:
    TTree();
    virtual ~TTree(){}

    bool empty() { return value == nullptr;}

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& node);
    void stream(std::ostream& os, const TTree& node, int height) const;

    Iter<TTree<T>, T> begin();
    std::shared_ptr<TTree<T>> GetNext();
    Iter<TTree<T>, T> end();

    std::shared_ptr<T> value;
    pTree left;
    pTree right;
    wTree prev;
};

template <class T>
TTree<T>::TTree()
    : value(nullptr)
    , left(nullptr)
    , right(nullptr)
    , prev()
{
}

template <class T>
std::shared_ptr<TTree<T>> TTree<T>::GetNext()
{
    pTree node = right;
    if (node)
        while (node->left)
            node = node->left;
    else {
        if (prev.lock() && prev.lock()->right.get() == this) {
            node = prev.lock();
            while (node->prev.lock() && node->prev.lock()->left != node)
                node = node->prev.lock();
            return node->prev.lock();
        }
        return prev.lock();
    }
    return node;
}

template <class T>
void TTree<T>::stream(std::ostream& os, const TTree<T>& node, int height) const
{
    if (node.right)
        stream(os, *node.right, height + 1);

    if (!node.value->empty()) {
        for (int i = 0; i < height; i++)
            os << "\t";

        node.value->Print();
        if (node.right || node.left)
            os << "<";

        os << std::endl;
    }

    if (node.left)
        stream(os, *node.left, height + 1);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TTree<T>& node)
{
    node.stream(os, node, 0);
    return os;
}

template <class T>
Iter<TTree<T>, T> TTree<T>::begin()
{
    TTree<T>* node = this;
    while (node->left)
        node = node->left.get();
    if (node->empty())
        node = nullptr;
    Iter<TTree<T>, T> res(node);
    return res;
}

template <class T>
Iter<TTree<T>, T> TTree<T>::end()
{
    Iter<TTree<T>, T> res(nullptr);
    return res;
}

#endif // TTREE_H
