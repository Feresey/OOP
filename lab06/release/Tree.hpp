#ifndef TREE_H
#define TREE_H

#include "TIterator.hpp"
#include "TTree.hpp"

template <class Container,class T>
class Tree {
private:
    pTree root;
    static std::shared_ptr<TAllocationBlock> allocator;

public:
    Tree(): root(new TTree<Container>()) {}

    Iter<TTree<Container>, Container> begin();
    Iter<TTree<Container>, Container> end();

    void add(T* figure, pTree node);
    void add(T* figure) { add(figure, root); }

    void Remove(pTree node);
    void Remove(char* path) { Remove(get(path)); }
    void Remove(fig criteria);
    void Remove(double criteria);

    pTree get(char* path);
    pTree get() { return get("\0"); }

    bool empty() { return root->empty(); }

    friend std::ostream& operator<<(std::ostream& os, const Tree<Container, T>& node) 
    { os << *node.root; return os;}
    void* operator new(size_t) { return allocator->allocate(); }
    void operator delete(void* p) { allocator->deallocate(p); }
};

#include "Tree.h"
#endif // !TREE_H