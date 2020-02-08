#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>

enum fig{tri,sqr,rec};

class Figure {
public:
    virtual double Square() = 0;
    virtual void Print(std::ostream& os) = 0;

    virtual bool empty() { return 0; }

    virtual ~Figure() = default;

    friend std::ostream& operator<<(std::ostream& os, const Figure& obj);
    virtual fig type() = 0;
};
#endif /* FIGURE_H */
