// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Sqr.hpp"

Sqr::Sqr()
    : Sqr(0)
{
}

Sqr::Sqr(size_t i)
    : side_a(i)
{
}

Sqr::Sqr(const Sqr& orig)
    : side_a(orig.side_a)
{
}

Sqr::Sqr(std::istream& is)
    : side_a(0)
{
    is >> side_a;
}

Sqr::~Sqr() {}

double Sqr::Square()
{
    return double(side_a) * double(side_a);
}

void Sqr::Print(std::ostream& os)
{
    os << *this;
}

Sqr& Sqr::operator=(const Sqr& right)
{
    if (this == &right)
        return *this;
    side_a = right.side_a;

    return *this;
}

Sqr& Sqr::operator++()
{
    side_a++;

    return *this;
}

Sqr operator+(const Sqr& left, const Sqr& right)
{
    return Sqr(left.side_a + right.side_a);
}

bool operator==(const Sqr& left, const Sqr& right)
{
    return left.side_a == right.side_a;
}

bool operator!=(const Sqr& left, const Sqr& right)
{
    return !(left == right);
}

std::ostream& operator<<(std::ostream& os, Sqr& obj)
{
    os << "(" << obj.side_a << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Sqr& obj)
{
    is >> obj.side_a;

    return is;
}
