#include "TTree.hpp"

template <class T>
TTree<T>::TTree()
    : value(nullptr)
    , left(nullptr)
    , right(nullptr)
    , prev()
{
}

template <class T>
bool TTree<T>::empty()
{
    return value == nullptr;
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
std::ostream& operator<<(std::ostream& os, const TTree<T>& Tree)
{
    Tree.stream(os, Tree, 0);

    return os;
}

template <class T>
void TTree<T>::add(T* figure, pTree node)
{
    if (empty()) {
        if (figure->Square() > 0)
            value.reset(figure);
        else
            delete figure;
        return;
    }
    if (figure->Square() <= 0) {
        delete figure;
        return;
    }
    if (figure->Square() >= value->Square()) // сбалансированное дерево
    {
        if (!right) {
            right.reset(new TTree());
            right->value.reset(figure);
            right->prev = node;
        } else
            right->add(figure, right);
    } else {
        if (!left) {
            left.reset(new TTree());
            left->value.reset(figure);
            left->prev = node;
        } else
            left->add(figure, left);
    }
}

template <class T>
pTree TTree<T>::getItem(char* path, pTree curr)
{

    if (*path == 'l') {
        if (left)
            return left->getItem(path + 1, left);
    } else if (*path == 'r') {
        if (right)
            return right->getItem(path + 1, right);
    } else if (*path != '\0') {
        return getItem(path + 1, curr);
    }
    return curr;
}

template <class T>
std::shared_ptr<T> TTree<T>::getValue(char* path, pTree curr)
{
    return getItem(path, curr)->value;
}

template <class T>
TTree<T>* TTree<T>::GetNext()
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
            return node->prev.lock().get();
        }
        return prev.lock().get();
    }
    return node.get();
}

/*
command>> -rlrr
————————————————————————————————————————————
                (5)
        (4)<
                        (3)
                (3)<
(3)<
        (2)
command>> -r
————————————————————————————————————————————
        (3)<
                (3)
(3)<
        (2)
*/

template <class T>
void TTree<T>::Remove(pTree node)
{
    if (!node->prev.lock()) {
        //!smf
        if (node->right) {
            std::swap(node->value, node->right->value);
            node = node->right;
        } else if (node->left) {
            std::swap(node->value, node->left->value);
            node = node->left;
        } else {
            node->value = nullptr;
            return;
        }
    }
    if (node->right && !node->left) {
        if (node->prev.lock()->right == node) {
            node->prev.lock()->right = node->right;
            node->right->prev = node->prev;
        } else if (node->prev.lock()->left == node) {
            node->prev.lock()->left = node->right;
            node->right->prev = node->prev;
        }
    } else if (node->left && !node->right) {
        if (node->prev.lock()->right == node) {
            node->prev.lock()->right = node->left;
            node->left->prev = node->prev;
        } else if (node->prev.lock()->left == node) {
            node->prev.lock()->left = node->left;
            node->left->prev = node->prev;
        }
    } else if (!node->right && !node->left) {
        if (node->prev.lock()->right == node)
            node->prev.lock()->right = nullptr;
        else if (node->prev.lock()->left == node)
            node->prev.lock()->left = nullptr;
    } else {
        pTree help = node->right;

        while (help->left) {
            help = help->left;
        }
        std::swap(node->value, help->value);
        Remove(help);
        return;
    }
    node->left = node->right = nullptr;
    node.reset();
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

template <class T>
TTree<T>::~TTree() {}

template <class T>
std::shared_ptr<TAllocationBlock> TTree<T>::allocator( new TAllocationBlock(sizeof(TTree<T>), 100500));

template <class T>
void* TTree<T>::operator new(size_t)
{
    return allocator->allocate();
}

template <class T>
void TTree<T>::operator delete(void* p)
{
    allocator->deallocate(p);
}

