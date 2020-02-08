#include "Tree.hpp"

Tree::Tree()
    : root(new TTree())
{
}

Tree::~Tree() {}

std::ostream& operator<<(std::ostream& os, const Tree& node)
{
    os << *node.root;
    return os;
}

pFigure Tree::getItem(char* path)
{
    return root->getValue(path, root);
}

pTree Tree::get(char* path)
{
    return root->getItem(path, root);
}
void Tree::Remove(char* path)
{
    root->Remove(root->getItem(path, root));
}

void Tree::add(Figure* triangle)
{
    root->add(triangle, root);
}

bool Tree::empty()
{
    return root->empty();
}