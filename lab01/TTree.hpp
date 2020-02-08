#ifndef TTREE_H
#define TTREE_H

#include "Triangle.hpp"
#include <iostream>
#include <memory>

class TTree {
public:
    TTree();
    TTree(const TTree& orig);

    Triangle* getItem();
    Triangle* getItem(char* path);

    void add(Triangle* triangle);
    void Remove(TTree* node);

    TTree* get(char* path);
    int height() const;
    bool empty();
    TTree& operator=(const TTree&);
    friend std::ostream& operator<<(std::ostream& os, const TTree& tree);
    ~TTree()
    {
        delete left;
        delete right;
        delete value;
    }

private:
    Triangle* value;
    TTree* left;
    TTree* right;
    TTree* prev;
};

#endif // TTREE_H
