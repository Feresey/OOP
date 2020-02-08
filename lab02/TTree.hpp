#ifndef TTREE_H
#define TTREE_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"

#define pFigure std::shared_ptr<Figure>
#define pTree std::shared_ptr<TTree>
#define wTree std::weak_ptr<TTree>

class TTree {
public:
    TTree();
    virtual ~TTree();

    pFigure getValue(char* path, pTree curr);

    void add(Figure* triangle, pTree node);
    void Remove(pTree node);

    pTree getItem(char* path, pTree curr);
    bool empty();
    void stream(std::ostream& os, const TTree& node, int height) const;
    friend std::ostream& operator<<(std::ostream& os, const TTree& tree);

    pFigure value;
    pTree left;
    pTree right;
    wTree prev;
};

#endif // TTREE_H
