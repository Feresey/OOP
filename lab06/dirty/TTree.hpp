#ifndef TTREE_H
#define TTREE_H

// #include "Rectangle.hpp"
// #include "Sqr.hpp"
#include "Queue.hpp"
#include "TAllocationBlock.hpp"
#include "TIterator.hpp"
// #include "Triangle.hpp"

#define pTree std::shared_ptr<TTree<T>>
#define wTree std::weak_ptr<TTree<T>>

template <class T>
class TTree {
public:
    TTree();
    virtual ~TTree();

    std::shared_ptr<T> getValue(char* path, pTree curr);
    std::shared_ptr<T> getValue() { return value; }

    void add(T* triangle, pTree node);
    void Remove(pTree node);

    pTree getItem(char* path, pTree curr);
    bool empty();
    void stream(std::ostream& os, const TTree& node, int height) const;
    TTree<T>* GetNext();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);

    void* operator new(size_t size);
    void operator delete(void* p);

    Iter<TTree<T>, TQueue<T>> begin();
    Iter<TTree<T>, TQueue<T>> end();

    std::shared_ptr<TQueue<T>> value;

protected:
    pTree left;
    pTree right;
    wTree prev;

    static std::shared_ptr<TAllocationBlock> allocator;
};

#include "TTree.h"

#endif // TTREE_H
