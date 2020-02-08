#ifndef TREE_H
#define TREE_H

#include "TIterator.hpp"
#include "TTree.hpp"

template <class T>
class Tree {
private:
    pTree root;
    static std::shared_ptr<TAllocationBlock> allocator;

public:
    Tree();
    ~Tree();

    Iter<TTree<T>, T> begin();
    Iter<TTree<T>, T> end();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const Tree<B>& node);

    void add(T* figure) { add(figure, root); }
    void add(T* figure, pTree node);
    void Remove(char* path) { Remove(get(path)); }
    void Remove(pTree node);
    void stream(std::ostream& os, const TTree<T>& node, int height) const;

    // template <class B>
    // friend std::ostream& operator<<(std::ostream& os, const TTree<B>& tree);

    pTree get(char* path);
    pTree get() { return get("\0"); }
    std::shared_ptr<T> getItem(char* path) { return get(path)->value; }
    bool empty();

    void* operator new(size_t size);
    void operator delete(void* p);
};

#include "Tree.h"
#endif // !TREE_H