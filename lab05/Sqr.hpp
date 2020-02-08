#ifndef Sqr_H
#define Sqr_H

#include "Figure.hpp"

class Sqr : public Figure {
public:
    Sqr();
    Sqr(size_t i);
    Sqr(const Sqr& orig);
    Sqr(std::istream& is);

    double Square() override;
    void Print() override;

    friend std::ostream& operator<<(std::ostream& os, Sqr& obj);
    friend std::istream& operator>>(std::istream& is, Sqr& obj);

    Sqr& operator++();
    friend Sqr operator+(const Sqr& left, const Sqr& right);

    Sqr& operator=(const Sqr& right);
    friend bool operator==(const Sqr& left, const Sqr& right);
    friend bool operator!=(const Sqr& left, const Sqr& right);

    virtual ~Sqr();

private:
    size_t side_a;
};

#endif //Sqr_H