#include "TTree.hpp"

tp
tpTree::TTree() : value(nullptr), left(nullptr), right(nullptr) {}

tp
bool tpTree::empty()
{
    return value == nullptr;
}

tp
std::ostream *tpTree::stream(std::ostream &os, const tpTree &node, int height) const
{
    if (node.right)
        stream(os, *node.right, height + 1);

    if (node.value && node.value->empty())
    {
        for (int i = 0; i < height; i++)
            os << "\t";

        node.value->Show(os);
        if (node.right || node.left)
            os << "<";

        os << std::endl;
    }

    if (node.left)
        stream(os, *node.left, height + 1);

    return &os;
}

  template <class A>
std::ostream &operator<<(std::ostream &os, const TTree<A> &Tree)
{

    Tree.stream(os, Tree, 0);

    return os;
}

tp
void tpTree::add(Figure *triangle)
{
    if (empty())
    {
        value = pFigure(triangle);
        return;
    }
    if (triangle->Square() <= 0)
    {
        delete triangle;
        return;
    }
    if (triangle->Square() >= value->Square())
    {
        if (!right)
        {
            right = pTree(new TTree());
            right->value = pFigure(triangle);
        }
        else
            right->add(triangle);
    }
    else
    {
        if (!left)
        {
            left = pTree(new TTree());
            left->value = pFigure(triangle);
        }
        else
            left->add(triangle);
    }
}

tp
pTree tpTree::getItem(char *path, pTree curr)
{
    if (*path == 'l')
    {
        if (left)
            return left->getItem(path + 1, left);
    }
    else if (*path == 'r')
    {
        if (right)
            return right->getItem(path + 1, right);
    }
    else if (*path != '\0')
    {
        return getItem(path + 1, curr);
    }
    return curr;
}

tp
std::shared_ptr<T> tpTree::getValue(char *path, pTree curr)
{
    return getItem(path, curr)->value;
}

tp
void tpTree::Remove(pTree node, pTree prev)
{

    if (prev)
    {

        if (prev == node)
        {

            return;
        }
        if (node->right && !node->left)
        {
            if (prev->right == node)
            {
                prev->right = node->right;
            }
            else if (prev->left == node)
            {
                prev->left = node->right;
            }
        }
        else if (node->left && !node->right)
        {
            if (prev->right == node)
            {
                prev->right = node->left;
            }
            else if (prev->left == node)
            {
                prev->left = node->left;
            }
        }
        else if (!node->right && !node->left)
        {
            if (prev->right == node)
                prev->right = nullptr;
            else if (prev->left == node)
                prev->left = nullptr;
        }
        else
        {
            pTree help;
            pTree pr = node;
            if (right)
            {
                help = node->right;
                while (help->left)
                {
                    pr = help;
                    help = help->left;
                }
                node->value.swap(help->value);
                Remove(help, pr);
            }
            if (left)
            {
                help = node->left;
                while (help->right)
                {
                    pr = help;
                    help = help->right;
                }
                node->value.swap(help->value);
                Remove(help, pr);
            }
            return;
        }
    }
    node->left = node->right = nullptr;
    node.reset();
}

tp
tpTree::~TTree() {}

template class TTree<Figure>;
template std::ostream &operator<<(std::ostream &os, const TTree<Figure> &tree);
