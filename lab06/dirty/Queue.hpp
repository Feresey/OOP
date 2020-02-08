#ifndef TQueue_H
#define TQueue_H

#include "Rectangle.hpp"
#include "Sqr.hpp"
#include "Triangle.hpp"

#include "TAllocationBlock.hpp"
#include "TIterator.hpp"

#define pQueue std::shared_ptr<TQueue<T>>
#define pQueueItem std::shared_ptr<TQueue<T>>

template <class TT>
struct QueueItem {
private:
    pQueueItem<TT> next;
    std::shared_ptr<TT> value;

public:
    QueueItem();
    ~QueueItem();
};

template <class T>
class TQueue {
public:
    TQueue();
    virtual ~TQueue();

    std::shared_ptr<T> getValue(char* path, pQueue curr);
    std::shared_ptr<T> getValue() { return value; }

    void add(T* triangle, pQueue node);
    void Remove(pQueue node);

    pQueue getItem(char* path, pQueue curr);
    bool empty();
    void stream(std::ostream& os, const TQueue& node, int height) const;
    TQueue<T>* GetNext();

    template <class B>
    friend std::ostream& operator<<(std::ostream& os, const TQueue<B>& Queue);

    void* operator new(size_t size);
    void operator delete(void* p);

    Iter<TQueue<T>, T> begin();
    Iter<TQueue<T>, T> end();

private:
    pQueueItem first;
    pQueueItem last;

    static std::shared_ptr<TAllocationBlock> allocator;
};

#include "Queue.h"

#endif // TQueue_H
