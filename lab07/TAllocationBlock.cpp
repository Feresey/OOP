#include "TAllocationBlock.hpp"
#include <iostream>

TAllocationBlock::TAllocationBlock(const size_t size, size_t count)
    : _size(size)
    , _count(count)
    , _used_blocks(static_cast<char*>(std::malloc(_size * _count)))
    , _free_blocks(static_cast<void**>(std::malloc(sizeof(void*) * _count)))
    , _free_count(0)
{
    for (size_t i = 0; i < _count; i++)
        _free_blocks[i] = _used_blocks + i * _size;
}

void* TAllocationBlock::allocate()
{
    void* result = nullptr;
    if (_free_count < _count) {
        result = _free_blocks[_free_count++];
    } else {
        throw 1;
    }
    return result;
}