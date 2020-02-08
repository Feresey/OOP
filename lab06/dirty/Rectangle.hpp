#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.hpp"
#include <cstdlib>
#include <iostream>

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(size_t i, size_t j);
    Rectangle(const Rectangle& orig);
    Rectangle(std::istream& is);

    double Square() override;
    void Print() override;

    friend std::ostream& operator<<(std::ostream& os, Rectangle& obj);
    friend std::istream& operator>>(std::istream& is, Rectangle& obj);

    Rectangle& operator++();
    friend Rectangle operator+(const Rectangle& left, const Rectangle& right);

    Rectangle& operator=(const Rectangle& right);
    friend bool operator==(const Rectangle& left, const Rectangle& right);
    friend bool operator!=(const Rectangle& left, const Rectangle& right);

    virtual ~Rectangle();

private:
    size_t side_a;
    size_t side_b;
};

#endif //RECTANGLE_H