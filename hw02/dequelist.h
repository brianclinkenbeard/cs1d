#ifndef DEQUELIST_H
#define DEQUELIST_H

#include "dlinkedlist.h"

template <class Type>
class DequeList
{
public:
    DequeList();
    void print() const;
    const Type& front() const;
    const Type& back() const;
    void insert_front(const Type& elem);
    void insert_back(const Type& elem);
    void remove_front();
    void remove_back();
private:
    DLinkedList<Type> D;
};

template <class Type>
DequeList<Type>::DequeList() {}

template <class Type>
void DequeList<Type>::print() const
{
    D.print();
}

template <class Type>
const Type& DequeList<Type>::front() const
{
    return D.front();
}

template <class Type>
const Type& DequeList<Type>::back() const
{
    return D.back();
}

template <class Type>
void DequeList<Type>::insert_front(const Type& elem)
{
    D.add_front(elem);
}

template <class Type>
void DequeList<Type>::insert_back(const Type& elem)
{
    D.add_back(elem);
}

template <class Type>
void DequeList<Type>::remove_front()
{
    D.remove_front();
}

template <class Type>
void DequeList<Type>::remove_back()
{
    D.remove_back();
}

#endif // DEQUELIST_H
