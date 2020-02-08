#include "Tree.hpp"
#define ELEM
#define qCount(queue) queue->count < 5

template <class Container, class T>
void Tree<Container, T>::add(T* figure, pTree node)
{
#ifdef ELEM
    if (empty() || qCount(node->value)) {
        if (figure->Square() > 0) {
            if (empty())
#else
    if (empty()) {
        if (figure->Square() > 0) {
#endif
                node->value.reset(new Container());
            node->value->add(figure);
        } else
            delete figure;
        return;
    }

    if (figure->Square() <= 0) {
        delete figure;
        return;
    }
#ifndef ELEM
    else if (figure->Square() == node->value->Square() && qCount(node->value)) {
        node->value->add(figure);
        return;
    }
#endif

    if (figure->Square() >= node->value->Square())
    {
        if (!node->right) {
            node->right.reset(new TTree<Container>());
            node->right->value.reset(new Container());
            node->right->value->add(figure);
            node->right->prev = node;
        } else
            add(figure, node->right);
    } else {
        if (!node->left) {
            node->left.reset(new TTree<Container>());
            node->left->value.reset(new Container());
            node->left->value->add(figure);
            node->left->prev = node;
        } else
            add(figure, node->left);
    }
}

template <class Container, class T>
pTree Tree<Container, T>::get(char* path)
{
    auto res = root;
    while (*path != '\0')
        switch (*path++) {
        case 'l':
            if (res->left)
                res = res->left;
            else
                return res;
            break;
        case 'r':
            if (res->right)
                res = res->right;
            else
                return res;
            break;
        default:
            continue;
        }
    return res;
}

template <class Container, class T>
void Tree<Container, T>::Remove(pTree node)
{
    if (node == root) {
        if (!node->right && node->left)
            root = node->left;
        else if (!node->left && node->right)
            root = node->right;
        else if (node->right || node->left) {
            std::swap(node->value, node->right->value);
            Remove(node->right);
        } else
            node->value = nullptr;

        return;
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

template <class Container, class T>
void Tree<Container, T>::Remove(fig criteria)
{
    auto i = root;
    std::shared_ptr<T> j(nullptr);
    while (i->left)
        i = i->left;
    for (; i != nullptr; i = i->GetNext()) {
        std::shared_ptr<Container> help(new Container());

        while (j = i->value->pop())
            if (j->type() != criteria) {
                help->add(j);
            }
        i->value = help;
    }
}

template <class Container, class T>
void Tree<Container, T>::Remove(double criteria)
{
    auto i = root;
    std::shared_ptr<T> j(nullptr);
    while (i->left)
        i = i->left;
    for (; i != nullptr; i = i->GetNext()) {
        std::shared_ptr<Container> help(new Container());

        while (j = i->value->pop())
            if (j->Square() < criteria) {
                help->add(j);
            }
        i->value = help;
    }
}

template <class Container, class T>
Iter<TTree<Container>, Container> Tree<Container, T>::begin()
{
    std::shared_ptr<TTree<Container>> node = root;
    while (node->left)
        node = node->left;
    if (node->empty())
        node = nullptr;
    Iter<TTree<Container>, Container> res(node);
    return res;
}

template <class Container, class T>
Iter<TTree<Container>, Container> Tree<Container, T>::end()
{
    Iter<TTree<Container>, Container> res(nullptr);
    return res;
}

template <class Container, class T>
std::shared_ptr<TAllocationBlock> 
Tree<Container, T>::allocator(new TAllocationBlock(sizeof(Tree<Container, T>), 500));
