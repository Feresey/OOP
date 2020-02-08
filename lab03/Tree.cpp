#include "Tree.hpp"

tp
ppTree::Tree() : root(new tpTree()) {}

tp
ppTree::~Tree() {}

tp
std::ostream &operator<<(std::ostream &os, const ppTree &node)
{
    os << *node.root;
    return os;
}

tp
std::shared_ptr<T> ppTree::getItem(char *path)
{
    return root->getValue(path, root);
}

// tp
// tpTree ppTree::get(char *path)
// {
//     return root->getItem(path, root);
// }

tp
void ppTree::Remove(char *path)
{

    int i = 0, it = 0;
    char tm;
    while (path[i] != '\0')
    {
        if (path[i] == 'r' || path[i] == 'l')
        {
            it = i;
        }
        i++;
    }
    tm = path[it];
    path[it] = '\0';
    pTree prev = root->getItem(path, root);
    path[it] = tm;
    if (!root->left && !root->right)
        root->value = nullptr;

    root->Remove(root->getItem(path, root), prev);
}

tp
void ppTree::add(T *triangle)
{
    root->add(triangle);
}

tp
bool ppTree::empty()
{
    return root->empty();
}

template class Tree<Figure>;
template std::ostream &operator<<(std::ostream &os, const Tree<Figure> &node);