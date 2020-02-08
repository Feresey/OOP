#ifndef TALLOCATIONBLOCK_H
#define TALLOCATIONBLOCK_H

#include <cstdlib>
#include <cstring>
class TAllocationBlock {
public:
    TAllocationBlock(size_t size, size_t count);
    TAllocationBlock(const TAllocationBlock& orig);
    TAllocationBlock& operator=(const TAllocationBlock& right);
    void* allocate();
    void deallocate(void* pointer);
    // bool has_free_blocks();

    virtual ~TAllocationBlock();

private:
    const size_t _size;
    size_t _count;

    char* _used_blocks;
    void** _free_blocks;

    size_t _free_count;
};

#endif /* TALLOCATIONBLOCK_H */
