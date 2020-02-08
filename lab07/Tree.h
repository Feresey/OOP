#include "Tree.hpp"

template <class T>
Tree<T>::Tree()
    : root(new TTree<T>())
{
}

template <class T>
void Tree<T>::USort()
{
    if (length() < 2)
        return;
    std::shared_ptr<T> middle = pop();
    Tree<T> left, right;

    while (!empty()) {
        std::shared_ptr<T> item = pop();
        if (item->Square() < middle->Square()) {
            left.add(item);
        } else {
            right.add(item);
        }
    }

    left.USort();
    right.USort();

    add(middle);
    add(left);
    add(right);
}

template <class T>
void Tree<T>::PSort()
{
    if (length() < 2)
        return;
    std::shared_ptr<T> middle = pop();
    Tree<T> left, right;

    while (!empty()) {
        std::shared_ptr<T> item = pop();
        if (item->Square() < middle->Square()) {
            left.add(item);
        } else {
            right.add(item);
        }
    }

    std::future<void> right_res = right.sort_in_background();
    std::future<void> left_res = left.sort_in_background();

    add(middle);

    left_res.get();

    add(left);

    right_res.get();

    add(right);
}

template <class T>
std::future<void> Tree<T>::sort_in_background()
{
    std::packaged_task<void(void)> task(std::bind(std::mem_fn(&Tree<T>::PSort), this));
    std::future<void> res(task.get_future());
    std::thread th(std::move(task));
    th.detach();
    return res;
}

template <class T>
void Tree<T>::add(Tree<T>& node)
{
    if (node.empty())
        return;
    if (node.root->value->Square() < root->value->Square())
        {
        root->left = node.root;
        root->left->prev = root;
    }
    else
    {
        root->right = node.root;
        root->right->prev = root;
    }
}

template <class T>
void Tree<T>::add(std::shared_ptr<T> figure, pTree node)
{
    if (figure->Square() <= 0)
        return;

    if (empty()) {
        node->value = figure;
        return;
    }

    int l = node->left ? node->left->height() : 0;
    int r = node->right ? node->right->height() : 0;

    if (r <= l)
    {
        if (!node->right) {
            node->right.reset(new TTree<T>());
            node->right->value = figure;
            node->right->prev = node;
        } else
            add(figure, node->right);
    } else {
        if (!node->left) {
            node->left.reset(new TTree<T>());
            node->left->value = figure;
            node->left->prev = node;
        } else
            add(figure, node->left);
    }
}

template <class T>
pTree Tree<T>::get(char* path)
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

template <class T>
void Tree<T>::Remove(pTree node)
{
    if (node == root) {
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
std::ostream& operator<<(std::ostream& os, const Tree<T>& node)
{
    os << *node.root;
    return os;
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

template <class T>
std::shared_ptr<TAllocationBlock> 
Tree<T>::allocator(new TAllocationBlock(sizeof(Tree<T>), 100500));

template <class T>
void* Tree<T>::operator new(size_t)
{
    return allocator->allocate();
}

template <class T>
void Tree<T>::operator delete(void* p)
{
    allocator->deallocate(p);
}

template <class T>
Tree<T>::~Tree() {}
