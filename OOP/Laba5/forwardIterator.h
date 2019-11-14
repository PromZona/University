#pragma once
#include <iterator>

template<typename T>
class DynamicArray;

template <typename T>
class forward_iterator : public std::iterator<std::input_iterator_tag, T>
{
    friend class DynamicArray<T>;

public:
    forward_iterator(const forward_iterator<T> &it);
    forward_iterator(T *p);

    bool operator!=(forward_iterator<T> const &other) const;
    bool operator==(forward_iterator<T> const &other) const; 
    typename forward_iterator<T>::reference operator*() const;
    forward_iterator<T> &operator++();

private:
    T *p;
};

template<typename T>
forward_iterator<T>::forward_iterator(T *P)
{
    p = P;
}

template<typename T>
forward_iterator<T>::forward_iterator(const forward_iterator<T> &it)
{
    p = it.p;
}

template<typename T>
bool forward_iterator<T>::operator!=(forward_iterator<T> const &other) const
{
    return p != other.p;
}

template<typename T>
bool forward_iterator<T>::operator==(forward_iterator<T> const &other) const
{
    return p == other.p;
}

template<typename T>
typename forward_iterator<T>::reference forward_iterator<T>::operator*() const
{
    return *p;
}

template<typename T>
forward_iterator<T>& forward_iterator<T>::operator++()
{
    ++p;
    return *this;
}