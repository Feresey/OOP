#include "Triangle.hpp"
#include <math.h>

Triangle::Triangle()
    : Triangle(0, 0, 0)
{
}

Triangle::Triangle(size_t a, size_t b, size_t c)
    : side_a(a)
    , side_b(b)
    , side_c(c)
{
}

Triangle::Triangle(const Triangle& orig)
    : side_a(orig.side_a)
    , side_b(orig.side_b)
    , side_c(orig.side_c)
{
}

Triangle::Triangle(std::istream& is)
    : side_a(0)
    , side_b(0)
    , side_c(0)
{
    is >> side_a;
    is >> side_b;
    is >> side_c;
}

Triangle::~Triangle() {}

double Triangle::Square()
{
    if (side_a == 0 || side_b == 0 || side_c == 0)
        return 0.0;
    double p = double(side_a + side_b + side_c) / 2.0;
    double res = p * (p - double(side_a)) * (p - double(side_b)) * (p - double(side_c));
    if (res <= 0.0)
        return 0.0;
    return sqrt(res);
}

void Triangle::Print(std::ostream& os)
{
    os << *this;
}

Triangle& Triangle::operator=(const Triangle& right)
{
    if (this == &right)
        return *this;
    side_a = right.side_a;
    side_b = right.side_b;
    side_c = right.side_c;

    return *this;
}

Triangle& Triangle::operator++()
{
    side_a++;
    side_b++;
    side_c++;

    return *this;
}

Triangle operator+(const Triangle& left, const Triangle& right)
{
    return Triangle(left.side_a + right.side_a, left.side_b + right.side_b, left.side_c + right.side_c);
}

bool operator==(const Triangle& left, const Triangle& right)
{
    return left.side_a == right.side_a && left.side_b == right.side_b;
}

bool operator!=(const Triangle& left, const Triangle& right)
{
    return !(left == right);
}

std::ostream& operator<<(std::ostream& os, Triangle& obj)
{
    os << "(" << obj.side_a << ',' << obj.side_b << ',' << obj.side_c << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& obj)
{
    is >> obj.side_a;
    is >> obj.side_b;
    is >> obj.side_c;

    return is;
}
