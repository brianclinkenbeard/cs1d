#ifndef CIRCULARVECTOR_H
#define CIRCULARVECTOR_H

#include "header.h"

template<class Type>

class CircularVector {
public:
    CircularVector();
    int size() const;
    bool empty() const;
    Type& at(int i);
    void erase(int i);
    void reserve(int N);
    void insert(int i, const Type& elem);
private:
    int cap;
    int elems;
    int front;
    int rear;
    Type* data;
};

template<class Type>
CircularVector<Type>::CircularVector()
{
    cap = 0;
    elems = 0;
    data = NULL;
    front = 0;
    rear = 0;
}

template<class Type>
int CircularVector<Type>::size() const
{
    return elems;
}

template<class Type>
bool CircularVector<Type>::empty() const
{
    return elems == 0;
}

template<class Type>
Type& CircularVector<Type>::at(int i)
{
    return data[i];
}

template<class Type>
void CircularVector<Type>::erase(int i)
{
    for (int j = i + 1; j < elems; j++)
        data[j - 1] = data[j];
    elems--;
    front = (front + 1) % cap;
}

template<class Type>
void CircularVector<Type>::reserve(int N)
{
    if (cap >= N)
        return;
    Type* temp = new Type[N];
    for (int j = 0; j < elems; j++)
        temp[j] = data[j];

    if (data != NULL)
        delete [] data;

    data = temp;
    cap = N;
    rear = cap - 1;
}

template<class Type>
void CircularVector<Type>::insert(int i, const Type &elem)
{
    if (elems >= cap)
        reserve(std::max(1, 2 * cap));

    for (int j = elems - 1; j >= i; j--)
        data[j+1] = data[j];

    data[i] = elem;
    elems++;
}

#endif // CIRCULARVECTOR_H
