#ifndef TREE_H
#define TREE_H

#include "TTree.hpp"

#define ppTree Tree<T>

tp class Tree
{
  friend class tpTree;

private:
  pTree root;

public:
  Tree();
  ~Tree();

  template <class A>
  friend std::ostream &operator<<(std::ostream &os, const Tree<A> &node);
  void Remove(char *path);
  void add(T *);
  tpTree get(char *path);
  std::shared_ptr<T> getItem(char *path);
  bool empty();
};


#endif // !TREE_H