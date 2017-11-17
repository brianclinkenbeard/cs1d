#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>

template <class Type>
struct Node {
    Type data;
    Node<Type> *prev_node;
    Node<Type> *next_node;
};


template <class Type>
class DLinkedList
{
public:
    DLinkedList();
    void print() const;
    const Type& front() const;
    const Type& back() const;
    void add_front(const Type& elem);
    void add_back(const Type& elem);
    void remove_back();
    void remove_front();
    ~DLinkedList();
private:
    Node<Type> *header;
    Node<Type> *trailer;
protected:
    void add(Node<Type> *insert_node, const Type& elem);
    void remove(Node<Type> *delete_node);

};

template <class Type>
DLinkedList<Type>::DLinkedList()
{
    header = new Node<Type>;
    trailer = new Node<Type>;
    header->next_node = trailer;
    trailer->prev_node = header;
}

template <class Type>
void DLinkedList<Type>::print() const
{
    Node<Type> *current_node = header->next_node;
    while (current_node != trailer) {
        std::cout << current_node->data << std::endl;
        current_node = current_node->next_node;
    }
}

template <class Type>
const Type& DLinkedList<Type>::front() const
{
    return header->next_node->data;
}

template <class Type>
const Type& DLinkedList<Type>::back() const
{
    return trailer->prev_node->data;
}

template <class Type>
void DLinkedList<Type>::add(Node<Type> *insert_node, const Type &elem)
{
    Node<Type>* temp = new Node<Type>;
    temp->data = elem;
    temp->next_node = insert_node;
    temp->prev_node = insert_node->prev_node;
    temp->prev_node->next_node = insert_node->prev_node = temp;
}

template <class Type>
void DLinkedList<Type>::add_front(const Type& elem)
{
    add(header->next_node, elem);
}

template <class Type>
void DLinkedList<Type>::add_back(const Type& elem)
{
    add(trailer, elem);
}

template <class Type>
void DLinkedList<Type>::remove(Node<Type> *delete_node)
{
    Node<Type> *temp = delete_node->prev_node;
    Node<Type> *buff = delete_node->next_node;
    temp->next_node = buff;
    buff->prev_node = temp;
    delete delete_node;
}

template <class Type>
void DLinkedList<Type>::remove_back()
{
    remove(trailer->prev_node);
}

template <class Type>
void DLinkedList<Type>::remove_front()
{
    remove(header->next_node);
}

template <class Type>
DLinkedList<Type>::~DLinkedList()
{
    while (header->next_node != trailer)
        remove_front();

    delete header;
    delete trailer;
}

#endif // DLINKEDLIST_H
