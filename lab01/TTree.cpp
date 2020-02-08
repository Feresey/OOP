#include "TTree.hpp"
// #include <utility>

TTree::TTree()
    : value(nullptr)
    , left(nullptr)
    , right(nullptr)
    , prev(nullptr)
{
}

TTree::TTree(const TTree& orig)
    : value(orig.value)
    , left(orig.left)
    , right(orig.right)
    , prev(orig.prev)
{
}

TTree& TTree::operator=(const TTree& orig)
{
    left = orig.left;
    right = orig.right;
    prev = orig.prev;
    value = orig.value;
    return *this;
}

int TTree::height() const
{
    if (!prev)
        return 0;
    return 1 + prev->height();
}

bool TTree::empty()
{
    return value;
}

std::ostream& operator<<(std::ostream& os, const TTree& Tree)
{
    Triangle help = Triangle();
    int height = Tree.height();

    if (Tree.right)
        os << *Tree.right;

    if (*Tree.value != help) {
        for (int i = 0; i < height; i++)
            os << "\t";

        if (*Tree.value != help)
            Tree.value->Print();
        else
            os << "empty!";

        if (Tree.right || Tree.left)
            os << "<";
        os << std::endl;
    }

    if (Tree.left)
        os << *Tree.left;

    return os;
}

void TTree::add(Triangle* triangle)
{
    if (!empty()) {
        value = triangle;
        return;
    }
    if (triangle->Square() <= 0) {
        return;
    }
    if (triangle->Square() >= value->Square()) 
    {
        if (!right) {
            right = new TTree();
            right->value = triangle;
            right->prev = this;
        } else
            right->add(triangle);
    } else {
        if (!left) {
            left = new TTree();
            left->value = triangle;
            left->prev = this;
        } else
            left->add(triangle);
    }
}

TTree* TTree::get(char* path)
{
    if (*path == 'l') {
        if (left)
            return left->get(path + 1);
    } else if (*path == 'r') {
        if (right)
            return right->get(path + 1);
    } else if (*path != '\0') {
        return get(path + 1);
    }
    return this;
}

Triangle* TTree::getItem()
{
    return value;
}

Triangle* TTree::getItem(char* path)
{
    return get(path)->value;
}

void TTree::Remove(TTree* node)
{
    if (!node->prev) {
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
        if (node->prev->right == node) {
            node->prev->right = node->right;
            node->right->prev = node->prev;
        } else if (node->prev->left == node) {
            node->prev->left = node->right;
            node->right->prev = node->prev;
        }
    } else if (node->left && !node->right) {
        if (node->prev->right == node) {
            node->prev->right = node->left;
            node->left->prev = node->prev;
        } else if (node->prev->left == node) {
            node->prev->left = node->left;
            node->left->prev = node->prev;
        }
    } else if (!node->right && !node->left) {
        if (node->prev->right == node)
            node->prev->right = nullptr;
        else if (node->prev->left == node)
            node->prev->left = nullptr;
    } else {
        TTree* help = node->right;

        while (help->left) {
            help = help->left;
        }
        std::swap(node->value, help->value);
        Remove(help);
        return;
    }
    node->left = node->right = node->prev = nullptr;
    delete node;
}
