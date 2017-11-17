#ifndef WRAPQUEUE_H
#define WRAPQUEUE_H

#include "linkeddeque.h"

template<class QueueType>
class WrapQueue
{
public:
    int size() const;
    bool empty() const;
    const QueueType& front() const;
    void enqueue(QueueType &elem);
    void dequeue();
private:
    linkedDeque<QueueType> myDeque;
};

template<class QueueType>
int WrapQueue<QueueType>::size() const
{
    return myDeque.size();
}

template<class QueueType>
bool WrapQueue<QueueType>::empty() const
{
    return myDeque.empty();
}

template<class QueueType>
const QueueType& WrapQueue<QueueType>::front() const
{
    return myDeque.front();
}

template<class QueueType>
void WrapQueue<QueueType>::enqueue(QueueType &elem)
{
    myDeque.insertBack(elem);
}

template<class QueueType>
void WrapQueue<QueueType>::dequeue()
{
    myDeque.removeFront();
}

#endif // WRAPQUEUE_H
