#ifndef ITER_H
#define ITER_H
#include <memory>

template <class node, class T>
class Iter {
public:
    Iter(std::shared_ptr<node> n)
        : node_ptr(n)
    {
    }

    std::shared_ptr<T> operator*()
    {
        return node_ptr->value;
    }

    std::shared_ptr<T> operator->()
    {
        return node_ptr->value;
    }

    Iter& operator++()
    {
        node_ptr = node_ptr->GetNext();
        return *this;
    }

    Iter operator++(int)
    {
        Iter iter(*this);
        ++(*this);
        return iter;
    }

    bool operator==(Iter const& i)
    {
        if (node_ptr == nullptr)
            return true;
        return node_ptr == i.node_ptr;
    }

    bool operator!=(Iter const& i)
    {
        return !(*this == i);
    }

private:
    std::shared_ptr<node> node_ptr;
};

#endif // !ITER_H
