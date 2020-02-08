#ifndef TALLOCATIONBLOCK_H
#define TALLOCATIONBLOCK_H

#include <cstdlib>
#include <cstring>
class TAllocationBlock {
private:
    const size_t _size;
    size_t _count;
    char* _used_blocks;
    void** _free_blocks;
    size_t _free_count;

public:
    TAllocationBlock(const size_t size, size_t count);

    void* allocate();
    void deallocate(void* pointer) { _free_blocks[--_free_count] = pointer; }

    virtual ~TAllocationBlock()
    {
        free(_free_blocks);
        free(_used_blocks);
    }
};

#endif /* TALLOCATIONBLOCK_H */
