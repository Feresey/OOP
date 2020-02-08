#ifndef TTREE_H
#define TTREE_H

#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Sqr.hpp"

#define pTree std::shared_ptr<TTree<T>>
#define tp template <class T>
#define tpTree TTree<T>
#define pFigure std::shared_ptr<Figure>

tp class TTree
{
public:
  TTree();
  virtual ~TTree();

  std::shared_ptr<T> getValue(char *path, pTree curr);

  void add(Figure *triangle);
  void Remove(std::shared_ptr<TTree<T>> node, std::shared_ptr<TTree<T>> prev);

  pTree getItem(char *path, pTree curr);
  bool empty();
  std::ostream *stream(std::ostream &os, const tpTree &node, int height) const;
  template <class B>
  friend std::ostream &operator<<(std::ostream &os, const TTree<B> &tree);

  // pFigure value;
  std::shared_ptr<T> value;
  pTree left;
  pTree right;
};

#endif // TTREE_H

// std::shared_ptr<TTree<Figure> >(((Tree<Figure>*)this)->Tree<Figure>::root))