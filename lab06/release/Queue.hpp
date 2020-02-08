#ifndef Queue_H
#define Queue_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"

#include "TIterator.hpp"
#include "TAllocationBlock.hpp"

#define pQueue std::shared_ptr<Queue<T>>
#define pQueueItem std::shared_ptr<QueueItem<T>>
#define wQueueItem std::weak_ptr<QueueItem<T>>

template <class T>
class QueueItem {
public:
    pQueueItem next;
    std::shared_ptr<T> value;

    QueueItem(): next(nullptr), value(nullptr) {}
    QueueItem(T* item): QueueItem() {value.reset(item);}
    QueueItem(std::shared_ptr<T> item): QueueItem() {value = item;}

    void SetNext(pQueueItem item)
    {
        pQueueItem old = next;
        next = item;
    }

    pQueueItem GetNext()
    {
        return next;
    }
};

template <class T>
class Queue {
private:
    pQueueItem first;
    wQueueItem last;

public:
    int count;

    Queue(): first(nullptr), last(first), count(0) {}

    Iter<QueueItem<T>, T> begin() { Iter<QueueItem<T>, T> res(first); return res; }
    Iter<QueueItem<T>, T> end() { Iter<QueueItem<T>, T> res(nullptr); return res; }

    void add(std::shared_ptr<T> item)
    {
        std::shared_ptr<QueueItem<T>> other = std::make_shared<QueueItem<T>>(item);
        count++;
        if (!first) {
            last = first = other;
            return;
        }
        last.lock()->SetNext(other);
        last = other;
    }
    void add(T* item)
    {
        std::shared_ptr<QueueItem<T>> other = std::make_shared<QueueItem<T>>(item);
        count++;
        if (!first) {
            last = first = other;
            return;
        }
        last.lock()->SetNext(other);
        last = other;
    }

    std::shared_ptr<T> pop()
    {
        std::shared_ptr<QueueItem<T>> elem = first;
        if (!elem)
            return nullptr;
        first = first->next;
        count--;
        return elem->value;
    }

    double Square() {
        double res = 0;
        auto iter = first;
        while(iter){
            res += iter->value->Square();
            iter = iter->next;
        }

        return res / count;
    }
    
    void Print(std::ostream& os) { os << *this; }
    bool empty() { return first.get() == nullptr; }

    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& q)
    {
        pQueueItem top = q.first;
        os << '[';
        while (top) {
            top->value->Print(os);
            top = top->next;
            if (top)
                os << ',';
        }
        os << ']';
        return os;
    }
};

#endif // Queue_H
