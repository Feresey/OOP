#include "Sqr.hpp"
#include <iostream>
#include <cmath>

Sqr::Sqr() : Sqr(0)
{
}

Sqr::Sqr(size_t a) : side_a(a)
{
    std::cout << "Sqr created: " << side_a << std::endl;
}

Sqr::Sqr(std::istream &is)
{
    is >> side_a;
}

Sqr::Sqr(const Sqr &orig)
{
    std::cout << "Sqr copy created" << std::endl;
    side_a = orig.side_a;
}

double Sqr::Square()
{
    return double(side_a * side_a);
}

void Sqr::Print()
{
    std::cout << "a=" << side_a << std::endl;
}

Sqr::~Sqr()
{
    std::cout << "Sqr deleted" << std::endl;
}
