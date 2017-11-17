#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H

#include "dlinkedlist.h"

template<class Type>
class linkedDeque {
public:
    linkedDeque();
    int size() const;
    bool empty() const;
    const Type& front() const; // returns a reference to front element
    const Type& back()const; // returns a reference to back element
    void insertFront(const Type& elem);
    void insertBack(const Type& elem);
    void removeFront();
    void removeBack();
private:
    doublyLinkedList<Type> D;
    int dSize;
};

template<class Type>
linkedDeque<Type>::linkedDeque() {
    dSize = 0;
}

template<class Type>
int linkedDeque<Type>::size() const {
    return dSize;
}

template<class Type>
bool linkedDeque<Type>::empty() const {
    return dSize == 0;
}

template<class Type>
const Type& linkedDeque<Type>::front() const {
    return D.front();
}

template<class Type>
const Type& linkedDeque<Type>::back() const {
    return D.back();
}

template<class Type>
void linkedDeque<Type>::insertFront(const Type& elem) {
    D.addFront(elem);
    dSize++;
}

template<class Type>
void linkedDeque<Type>::insertBack(const Type& elem) {
    D.addBack(elem);
    dSize++;
}

template<class Type>
void linkedDeque<Type>::removeFront() {
    D.removeFront();
    dSize--;
}

template<class Type>
void linkedDeque<Type>::removeBack() {
    D.removeBack();
    dSize--;
}

#endif // LINKEDDEQUE_H
