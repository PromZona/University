#pragma once
#include <iostream>
#include <iterator>
#include <memory>
#include <math.h>
#include "stackallocator.h"

#define OUT_OF_RANGE 1
#define DOES_NOT_EXIST 2
#define TRY_TO_DELETE_EMPTY 3
#define INSERT_IN_HOLDED_PLACE 4
#define ITERATOR_DONT_EXIST 5

class SixthAngle
{
public:
    void printVertices()
    {
        std::cout << "<" << a.first << ", " << a.second << ">\n";
        std::cout << "<" << b.first << ", " << b.second << ">\n";
        std::cout << "<" << c.first << ", " << c.second << ">\n";
        std::cout << "<" << d.first << ", " << d.second << ">\n";
        std::cout << "<" << e.first << ", " << e.second << ">\n";
        std::cout << "<" << f.first << ", " << f.second << ">\n";
        std::cout << std::endl;
    }

    int distanceBetween(std::pair<int, int> first, std::pair<int, int> second)
    {
        int fir = pow((abs(second.first - first.first)), 2);
        int sec = pow((abs(second.second - first.second)), 2);
        return (int)sqrt(fir + sec);
    }

    float Area()
    {
        float edge = distanceBetween(a, b);
        float mulconst = 3 * sqrt(3) / 2;
        return (mulconst * pow(edge, 2));
    }

    friend std::istream &operator>>(std::istream &in, SixthAngle &fig)
    {
        char a;
        int x, y;
        in >> x >> a >> y;
        fig.a = {x, y};
        in >> x >> a >> y;
        fig.b = {x, y};
        in >> x >> a >> y;
        fig.c = {x, y};
        in >> x >> a >> y;
        fig.d = {x, y};
        in >> x >> a >> y;
        fig.e = {x, y};
        in >> x >> a >> y;
        fig.f = {x, y};
        return in;
    }

    std::pair<int, int> a, b, c, d, e, f;
    bool isExist = false;
};

template <class T>
class DynamicArray
{
public:
    typedef T *iterator;
    typedef T *const_iterator;

    DynamicArray();
    ~DynamicArray();
    T *operator[](int index);
    T *returnIterator(int index);
    int size();
    void add(T *obj);
    iterator begin();
    iterator end();
    void insert(iterator it, T obj);
    void erase(iterator it);


    iterator _empty;
private:
    int lenght;    //max Accessable size
    int nextIndex; // next index to write
    std::shared_ptr<T *[]> storage;
    iterator _begin;
    iterator _end;
};

template <class T>
DynamicArray<T>::DynamicArray()
{
    _empty = new T();
    _empty->isExist = false;
    storage = std::shared_ptr<T *[]>(new T *[10]);
    for (int i = 0; i < 10; i++)
        storage[i] = _empty;
    _begin = storage[0];
    _end = storage[0];
    lenght = 10;
    nextIndex = 0;
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
}

template <class T>
T *DynamicArray<T>::operator[](int index)
{
    T *out;
    if (index > nextIndex - 1)
        throw OUT_OF_RANGE;
    out = storage[index];
    return out;
}

template <class T>
T *DynamicArray<T>::returnIterator(int index)
{
    iterator out;
    if (index > nextIndex - 1)
        throw OUT_OF_RANGE;
    if (storage[index] == _empty)
        throw DOES_NOT_EXIST;
    out = storage[index];
    return out;
}

template <class T>
int DynamicArray<T>::size()
{
    return nextIndex;
}

template <class T>
void DynamicArray<T>::add(T *obj)
{
    if (nextIndex == lenght)
    {
        lenght = lenght + 1;
        std::shared_ptr<T *[]> storagenew(new T *[lenght]);
        for (int i = 0; i < nextIndex; i++)
            storagenew[i] = storage[i];
        for (int j = nextIndex; j < lenght; j++)
            storagenew[j] = _empty;
        storage = storagenew;
    }
    obj->isExist = true;
    storage[nextIndex++] = obj;
    if ((nextIndex - 1) == 0)
        _begin = storage[0];
    _end = storage[nextIndex - 1];
}

template <class T>
typename DynamicArray<T>::iterator DynamicArray<T>::begin()
{
    return _begin;
}

template <class T>
typename DynamicArray<T>::iterator DynamicArray<T>::end()
{
    return _end;
}

template <class T>
void DynamicArray<T>::insert(iterator it, T obj)
{
    for (int i = 0; i < lenght; i++)
    {
        if (it == &storage[i])
        {
            if (it->isExist == true)
                throw INSERT_IN_HOLDED_PLACE;
            obj.isExist = true;
            storage[i] = obj;
            return;
        }
    }
    throw ITERATOR_DONT_EXIST;
}

template <class T>
void DynamicArray<T>::erase(iterator it)
{
    for (int i = 0; i < lenght; i++)
    {
        if (it == storage[i])
        {
            if (it == _empty)
                throw TRY_TO_DELETE_EMPTY;
            if (storage[i] == _end)
                _end = _end - 1;
            storage[i] = _empty;
            return;
        }
    }
    throw ITERATOR_DONT_EXIST;
}