#include "Rectangle.hpp"

Rectangle::Rectangle() : Rectangle(0, 0) {}

Rectangle::Rectangle(size_t i, size_t j) : Figure(), side_a(i), side_b(j) {}

Rectangle::Rectangle(const Rectangle &orig)
{
    side_a = orig.side_a;
    side_b = orig.side_b;
}

Rectangle::Rectangle(std::istream &is)
{
    is >> side_a;
    is >> side_b;
}

Rectangle::~Rectangle() {}

double Rectangle::Square()
{

    return side_a * side_b;
}

void Rectangle::Print()
{
    std::cout << "a=" << side_a << ", b=" << side_b << std::endl;
}

Rectangle &Rectangle::operator=(const Rectangle &right)
{
    if (this == &right)
        return *this;
    side_a = right.side_a;
    side_b = right.side_b;

    return *this;
}

Rectangle &Rectangle::operator++()
{
    side_a++;
    side_b++;

    return *this;
}

Rectangle operator+(const Rectangle &left, const Rectangle &right)
{
    return Rectangle(left.side_a + right.side_a, left.side_b + right.side_b);
}

bool operator==(const Rectangle &left, const Rectangle &right)
{
    return left.side_a == right.side_a && left.side_b == right.side_b;
}

bool operator!=(const Rectangle &left, const Rectangle &right)
{
    return !(left == right);
}

std::ostream &operator<<(std::ostream &os, const Rectangle &obj)
{
    os << "(" << obj.side_a << "," << obj.side_b << ')';
    return os;
}

std::istream &operator>>(std::istream &is, Rectangle &obj)
{
    is >> obj.side_a;
    is >> obj.side_b;

    return is;
}

std::ostream *Rectangle::Show(std::ostream &os)
{
    os << *this;
    // std::cout << *this << '\n';
    return &os;
}