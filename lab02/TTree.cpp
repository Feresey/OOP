#include "TTree.hpp"

TTree::TTree()
    : value(nullptr)
    , left(nullptr)
    , right(nullptr)
    , prev()
{
}

bool TTree::empty()
{
    return value == nullptr;
}

void TTree::stream(std::ostream& os, const TTree& node, int height) const
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

std::ostream& operator<<(std::ostream& os, const TTree& Tree)
{
    Tree.stream(os, Tree, 0);

    return os;
}

void TTree::add(Figure* figure, pTree node)
{
    if (empty()) {
        if (figure->Square() > 0)
            value.reset(figure);
        else
            delete figure;
        return;
    }
    if (figure->Square() <= 0) {
        return;
    }
    if (figure->Square() >= value->Square())
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

pTree TTree::getItem(char* path, pTree curr)
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

pFigure TTree::getValue(char* path, pTree curr)
{
    return getItem(path, curr)->value;
}

void TTree::Remove(pTree node)
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

TTree::~TTree() {}
