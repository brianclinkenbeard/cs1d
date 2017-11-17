#ifndef SINGLESTACK_H
#define SINGLESTACK_H

#include <iostream>

template <class Type>
struct NodeType {
    Type data;
    NodeType<Type> *prev_node;
};

template <class Type>
class SingleStack
{
public:
    SingleStack();
    bool is_empty() const;
    void print() const;
    void push(const Type& data);
    void pop();
    Type get_top();
    ~SingleStack();
private:
    NodeType<Type> *top;
};

template <class Type>
SingleStack<Type>::SingleStack()
{
    top = NULL;
}

template <class Type>
bool SingleStack<Type>::is_empty() const
{
    return top == NULL;
}

template <class Type>
void SingleStack<Type>::print() const
{
    NodeType<Type> *current_ptr = top;

    while (current_ptr != NULL) {
        std::cout << current_ptr->data << std::endl;
        current_ptr = current_ptr->prev_node;
    }
}

template <class Type>
void SingleStack<Type>::push(const Type& new_element)
{
    NodeType<Type> *new_node = new NodeType<Type>;
    new_node->data = new_element;
    new_node->prev_node = top;
    top = new_node;
}

template <class Type>
void SingleStack<Type>::pop()
{
    NodeType<Type> *pop_node = top;
    top = pop_node->prev_node;

    delete pop_node;
}

template <class Type>
Type SingleStack<Type>::get_top()
{
    return top->data;
}

template <class Type>
SingleStack<Type>::~SingleStack()
{
    NodeType<Type> *delete_node = top;

    while (top != NULL) {
        delete_node = top;
        top = top->prev_node;
        delete delete_node;
    }
}

#endif // SINGLESTACK_H
