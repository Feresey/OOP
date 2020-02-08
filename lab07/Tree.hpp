#ifndef TREE_H
#define TREE_H

#include "TIterator.hpp"
#include "TTree.hpp"
#include <functional>
#include <future>
#include <mutex>

template <class T>
class Tree {
private:
    pTree root;
    static std::shared_ptr<TAllocationBlock> allocator;
    std::future<void> sort_in_background();

    ulong length()
    {
        ulong res = 0;
        for (auto i = this->begin(); i != this->end(); i++)
            res++;
        return res;
    }
    void USort();
    void PSort();
    std::shared_ptr<T> pop()
    {
        auto res = root->value;
        Remove(root);
        return res;
    }
    void add(Tree&);

public:
    Tree();
    ~Tree();

    Iter<TTree<T>, T> begin();
    Iter<TTree<T>, T> end();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const Tree<B>& node);

    void add(std::shared_ptr<T> figure) { add(figure, root); }
    void add(std::shared_ptr<T> figure, pTree node);
    void Remove(char* path) { Remove(get(path)); }
    void Remove(pTree node);
    void stream(std::ostream& os, const TTree<T>& node, int height) const;

    pTree get(char* path);
    void Sort(char choice)
    {
        switch (choice) {
        case 'p':
            PSort();
            break;
        case 'u':
            USort();
            break;
        }
    }
    pTree get() { return get("\0"); }
    std::shared_ptr<T> getItem(char* path) { return get(path)->value; }
    bool empty();

    void* operator new(size_t size);
    void operator delete(void* p);
};

#include "Tree.h"
#endif // !TREE_H