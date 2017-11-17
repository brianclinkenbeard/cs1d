#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>

template <class Type>
class CircularQueue
{
public:
    CircularQueue(int new_max = 100);
    void print();
    void enqueue(Type);
    void dequeue();
    Type get_front();
private:
    int count, rear, front, max;
    Type *list;
};

template <class Type>
CircularQueue<Type>::CircularQueue(int new_max)
{
    max = new_max;
    front = 0;
    count = 0;
    rear = new_max - 1;
    list = new Type[max];
}

template <class Type>
void CircularQueue<Type>::print()
{
    int i = front;
    while (i <= rear) {
        std::cout << list[i] << std::endl;
        i = (i + 1) % max;
    }
}

template <class Type>
void CircularQueue<Type>::enqueue(Type new_element)
{
    // advance rear
    rear = (rear + 1) % max;

    count++;
    list[rear] = new_element;
}

template <class Type>
void CircularQueue<Type>::dequeue()
{
    count--;
    // advance front
    front = (front + 1) % max;
}

template <class Type>
Type CircularQueue<Type>::get_front()
{
    return list[front];
}

#endif // CIRCULARQUEUE_H
