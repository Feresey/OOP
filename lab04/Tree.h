#include "Tree.hpp"

template <class T>
Tree<T>::Tree()
    : root(new TTree<T>())
{
}

template <class T>
Tree<T>::~Tree() {}

template <class T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& node)
{
    os << *node.root;
    return os;
}

template <class T>
std::shared_ptr<T> Tree<T>::getItem(char* path)
{
    return root->getValue(path, root);
}

template <class T>
pTree Tree<T>::get(char* path)
{
    return root->getItem(path, root);
}
template <class T>
void Tree<T>::Remove(char* path)
{
    root->Remove(root->getItem(path, root));
}

template <class T>
void Tree<T>::add(Figure* triangle)
{
    root->add(triangle, root);
}

template <class T>
bool Tree<T>::empty()
{
    return root->empty();
}

template <class T>
Iter<TTree<T>, T> Tree<T>::begin()
{
    std::shared_ptr<TTree<T>> node = root;
    while (node->left)
        node = node->left;
    if (node->empty())
        node = nullptr;
    Iter<TTree<T>, T> res(node);
    return res;
}

template <class T>
Iter<TTree<T>, T> Tree<T>::end()
{
    Iter<TTree<T>, T> res(nullptr);
    return res;
}