#ifndef LISTPRIORITYQUEUE_H
#define LISTPRIORITYQUEUE_H

#include <list>

template <typename E, typename C>
class ListPriorityQueue
{
public:
    int size() const;        /* Number of elements */
    bool empty() const;      /* Is the queue empty? */
    void insert(const E& e); /* Insert element */
    const E& min() const;    /* Minimum element */
    void removeMin();        /* Remove minimum */
private:
    std::list<E> L;          /* Priority queue contents */
    C isLess;                /* Less-than comparator */
};

/* Insert element */
template <typename E, typename C>
void ListPriorityQueue<E,C>::insert(const E& e) {
    typename std::list<E>::iterator p;
    p = L.begin();

    while (p != L.end() && !isLess(e, *p))
        ++p;

    L.insert(p, e);
}

template <typename E, typename C>
const E& ListPriorityQueue<E,C>::min() const
{
    return L.back();
}

template <typename E, typename C>
void ListPriorityQueue<E,C>::removeMin()
{
    L.pop_back();
}

template <typename E, typename C>
int ListPriorityQueue<E,C>::size() const
{
    return L.size();
}

template <typename E, typename C>
bool ListPriorityQueue<E,C>::empty() const
{
    return L.empty();
}


#endif // LISTPRIORITYQUEUE_H
