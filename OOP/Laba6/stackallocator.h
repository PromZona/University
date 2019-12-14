#pragma once

template <class T, size_t BLOCKS_COUNT>
class StackAllocator
{
private:
    size_t _count = 0;
    T* _buffer;
    T* _last;

public:
    using value_type = T;
    using pointer = T *;

    StackAllocator()
    {
        _buffer = (T*)malloc(BLOCKS_COUNT * sizeof(value_type));
    }

    ~StackAllocator()
    {
        free(_buffer);
    }

    pointer Allocate()
    {
        if((BLOCKS_COUNT - _count) < 1)
        {
            throw std::bad_alloc();
        }

        pointer ret = (_buffer + _count);
        _count++;
        return ret;
    }

    void DeAllocate(pointer ptr)
    {
        if ((_buffer + _count - 1) == ptr)
        {
            _count--;
        }
    }

};