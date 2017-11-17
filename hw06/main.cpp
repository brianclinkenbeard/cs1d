#include <iostream>
#include <string>
#include "heappriorityqueue.h"

/*
 * Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 6
 * This program will create a heap sort using the Author's implementation.
 * It will first show each intermediate heap while adding the nodes to the heap.
 * It will follow by showing each intermediate heap while removing all the nodes.
 */
int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 6\n"
              << "This program will create a heap sort using the Author's implementation.\n"
              << "It will first show each intermediate heap while adding the nodes to the heap.\n"
              << "It will follow by showing each intermediate heap while removing all the nodes.\n"
              << std::endl;

    // create a team struct
    struct team {
        int key;
        std::string name;
    };

    // create a compare struct
    struct compare {
        bool operator()(const team& lhs, const team& rhs) const
        {
            return lhs.key <= rhs.key;
        }
    };

    HeapPriorityQueue<team, compare> heap_queue;

    team team_list[10] = { { 44, "Rams" }, { 22, "Vikings" }, { 88, "Lions" }, { 47, "Dolphins" }, { 123, "Patriots" },
                           { 44, "Bengals" }, { 69, "Packers" }, { 24, "Broncos" }, { 13, "Bears" }, { 42, "Chargers" } };

    std::cout << "Showing each intermediate heap while adding the nodes:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        // insert
        heap_queue.insert(team_list[i]);
        // print
        std::cout << "Heap:" << std::endl;
        for (HeapPriorityQueue<team, compare> print_heap = heap_queue; !print_heap.empty(); print_heap.removeMin())
            std::cout << print_heap.min().key << " " << print_heap.min().name << std::endl;
        std::cout << std::endl;
    }

    std::vector<team> min_heap;

    std::cout << "Showing each intermediate heap while removing all the nodes:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        // print
        std::cout << "Heap:" << std::endl;
        for (HeapPriorityQueue<team, compare> print_heap = heap_queue; !print_heap.empty(); print_heap.removeMin())
            std::cout << print_heap.min().key << " " << print_heap.min().name << std::endl;
        std::cout << std::endl;

        min_heap.push_back(heap_queue.min());
        heap_queue.removeMin();
    }

    std::cout << "Final sorted heap: " << std::endl;
    for (unsigned int i = 0; i < min_heap.size(); ++i)
        std::cout << min_heap.at(i).key << " " << min_heap.at(i).name << std::endl;

    return 0;
}
