#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>
class Figure {
public:
    virtual double Square() = 0;
    virtual void Print() = 0;

    virtual bool empty() { return 0; }

    virtual ~Figure() = default;

    friend std::ostream& operator<<(std::ostream& os, const Figure& obj);
};
#endif /* FIGURE_H */
