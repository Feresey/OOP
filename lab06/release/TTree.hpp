#ifndef TTREE_H
#define TTREE_H

#include "Queue.hpp"
#include "TAllocationBlock.hpp"
#include "TIterator.hpp"

#define pTree std::shared_ptr<TTree<Container>>
#define wTree std::weak_ptr<TTree<Container>>

template <class Container>
class TTree {
public:
    TTree();

    bool empty() { return value == nullptr; }

    friend std::ostream& operator<<(std::ostream& os, const TTree<Container>& node) 
    { node.stream(os, node, 0); return os; }
    void stream(std::ostream& os, const TTree& node, int height) const;

    std::shared_ptr<TTree<Container>> GetNext();

    std::shared_ptr<Container> value;
    pTree left;
    pTree right;
    wTree prev;
};

template <class Container>
TTree<Container>::TTree()
    : value(nullptr)
    , left(nullptr)
    , right(nullptr)
{
}

template <class Container>
std::shared_ptr<TTree<Container>> TTree<Container>::GetNext()
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

template <class Container>
void TTree<Container>::stream(std::ostream& os, 
                              const TTree<Container>& node,
                              int height) const
{
    if (!node.value)
        return;
    if (node.right)
        stream(os, *node.right, height + 1);

    if (!node.value->empty()) {
        for (int i = 0; i < height; i++)
            os << '\t';

        node.value->Print(os);
        if (node.right || node.left)
            os << '<';

        os << '\n';
    }

    if (node.left)
        stream(os, *node.left, height + 1);
}

#endif // TTREE_H
