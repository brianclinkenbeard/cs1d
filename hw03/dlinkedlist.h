#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "header.h"

template<class Type>
struct dNodeType {
    dNodeType *next;
    dNodeType *prev;
    Type info;
};

template<class Type>
class doublyLinkedList {
public:
    doublyLinkedList();
    ~doublyLinkedList();
    bool empty() const;
    const Type& front() const; // return a reference to front element
    const Type& back() const; // return a reference to back element
    void addFront(const Type& elem);
    void addBack(const Type& elem);
    void removeBack();
    void removeFront();
private:
    dNodeType<Type> *header;
    dNodeType<Type> *trailer;
protected:
    void add(dNodeType<Type> *node, const Type& elem);
    void remove(dNodeType<Type> *node);
};

template<class Type>
doublyLinkedList<Type>::doublyLinkedList() {
    header = new dNodeType<Type>;
    trailer = new dNodeType<Type>;
    header->next = trailer;
    trailer->prev = header;
}

template<class Type>
doublyLinkedList<Type>::~doublyLinkedList() {
    while (!empty())
        removeFront();
    delete header;
    delete trailer;
}

template<class Type>
bool doublyLinkedList<Type>::empty() const {
    return header->next == trailer;
}

template<class Type>
const Type& doublyLinkedList<Type>::front() const {
    return header->next->info;
}

template<class Type>
const Type& doublyLinkedList<Type>::back() const {
    return trailer->prev->info;
}

template<class Type>
void doublyLinkedList<Type>::add(dNodeType<Type> *node, const Type& elem) {
    dNodeType<Type> *temp = new dNodeType<Type>;
    temp->info = elem;
    temp->next = node;
    temp->prev = node->prev;
    temp->prev->next = node->prev = temp;
}

template<class Type>
void doublyLinkedList<Type>::addFront(const Type &elem) {
    add(header->next, elem);
}

template<class Type>
void doublyLinkedList<Type>::addBack(const Type &elem) {
    add(trailer, elem);
}

template<class Type>
void doublyLinkedList<Type>::remove(dNodeType<Type> *node) {
    dNodeType<Type> *temp = node->prev;
    dNodeType<Type> *buff = node->next;
    temp->next = buff;
    buff->prev = temp;
    delete node;
}

template<class Type>
void doublyLinkedList<Type>::removeFront() {
    remove(header->next);
}

template<class Type>
void doublyLinkedList<Type>::removeBack() {
    remove(trailer->prev);
}

#endif // DLINKEDLIST_H
