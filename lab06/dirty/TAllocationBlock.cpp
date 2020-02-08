#include "TAllocationBlock.hpp"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count)
    : _size(size)
    , _count(count)
    , _used_blocks(static_cast<char*>(std::malloc(_size * _count)))
    , _free_blocks(static_cast<void**>(std::malloc(sizeof(void*) * _count)))
    , _free_count(0)
{
    for (size_t i = 0; i < _count; i++)
        _free_blocks[i] = _used_blocks + i * _size;
    std::cout << "TAllocationBlock: Memory init" << std::endl;
}

TAllocationBlock::TAllocationBlock(const TAllocationBlock& org)
    : _size(org._size)
    , _count(org._count)
    , _used_blocks(org._used_blocks)
    , _free_blocks(org._free_blocks)
    , _free_count(org._free_count)
{
}

TAllocationBlock& TAllocationBlock::operator=(const TAllocationBlock& right)
{
    // _size = right._size;
    _count = right._count;
    free(_used_blocks);
    _used_blocks = right._used_blocks;
    free(_free_blocks);
    _free_blocks = right._free_blocks;
    _free_count = right._free_count;
    return *this;
}

void* TAllocationBlock::allocate()
{
    void* result = nullptr;
// add:
    if (_free_count < _count) {
        result = _free_blocks[_free_count++];
        // _free_count--;
        // std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) << " of " << _count << std::endl;
    } else {
        // size_t count = _count * 2;
        // char* new_used_blocks = static_cast<char*>(std::malloc(_size * count));
        // void** new_free_blocks = static_cast<void**>(std::malloc(sizeof(void*) * count));
        // memcpy(new_used_blocks, _used_blocks, _size * _count);
        // // memcpy(new_free_blocks, _free_blocks, sizeof(void*) * _count);
        // for (size_t i = 0; i < count; ++i)
        //     new_free_blocks[i] = new_used_blocks + i * _size;
        // // delete _used_blocks;
        // free(_free_blocks);
        // // free(_used_blocks);
        // _used_blocks = new_used_blocks;
        // _free_blocks = new_free_blocks;
        // // _free_count += _count;
        // _count = count;
        // goto add;
        // std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
        throw 1;
    }

    return result;
}

void TAllocationBlock::deallocate(void* pointer)
{
    // std::cout << "TAllocationBlock: Deallocate block " << std::endl;
    _free_blocks[--_free_count] = pointer;
    // _free_count++;
}

// bool TAllocationBlock::has_free_blocks()
// {
//     return _free_count > 0;
// }

TAllocationBlock::~TAllocationBlock()
{
    // if (_free_count >= _count)
    //     std::cout << "TAllocationBlock: Memory leak?" << std::endl;
    // else
    //     std::cout << "TAllocationBlock: Memory freed" << std::endl;
    if (_free_blocks)
        free(_free_blocks);
    if (_used_blocks)
        free(_used_blocks);
}
