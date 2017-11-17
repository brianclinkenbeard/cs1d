#include "wrapqueue.h"
#include "circularvector.h"

/*
 * Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 3
 * This program will implement and demonstrate the functionality of a Queue interface
 * with a class that is wrapped on the LinkedDeque and DLinkedList classes. It will then
 * demonstrate a vector ADT by means of an extendable array used in a circular fashion
 * and print the circular array before and after each insertion and deletion.
 */

int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 3\n"
              << "This program will implement and demonstrate the functionality of a Queue interface \n"
              << "with a class that is wrapped on the LinkedDeque and DLinkedList classes. It will then \n"
              << "demonstrate a vector ADT by means of an extendable array used in a circular fashion \n"
              << "and print the circular array before and after each insertion and deletion. \n"
              << std::endl;

    // PART 1
    std::cout << "Creating queue..." << std::endl;
    WrapQueue<std::string> test_queue;

    std::string words[4] = {"A man, a plan, a canal, Panama",
                           "Was it a car or a cat I saw?",
                           "Sit on a potato pan, Otis",
                           "No lemon, no melon"};

    if (test_queue.empty())
        std::cout << "Queue is empty." << std::endl;

    std::cout << "Initial size: " << test_queue.size() << std::endl;

    std::cout << "Enqueueing strings..." << std::endl;
    for (int i = 0; i < 4; ++i)
        test_queue.enqueue(words[i]);
    std::cout << "New size: " << test_queue.size() << std::endl;

    if (!test_queue.empty())
        std::cout << "Queue is not empty." << std::endl;

    std::cout << "Dequeueing and printing front elements..." << std::endl;
    for (WrapQueue<std::string> print = test_queue; !print.empty(); print.dequeue()) {
        std::cout << print.front() << std::endl;
    }

    std::cout << std::endl;

    // PART 2
    std::cout << "Creating circular vector..." << std::endl;
    CircularVector<std::string> test_vector;

    std::cout << "Initial size: " << test_vector.size() << std::endl;

    if (test_vector.empty())
        std::cout << "Vector is empty." << std::endl;

    std::cout << "Inserting string at the rear..." << std::endl;
    test_vector.insert(0, words[0]);

    std::cout << "Printing contents of vector..." << std::endl;
    for (int i = 0; i < test_vector.size(); ++i)
        std::cout << i << ": " << test_vector.at(i) << std::endl;

    std::cout << "Inserting string at the front..." << std::endl;
    test_vector.insert(1, words[3]);

    std::cout << "Printing contents of vector..." << std::endl;
    for (int i = 0; i < test_vector.size(); ++i)
        std::cout << i << ": " << test_vector.at(i) << std::endl;

    std::cout << "Inserting strings to the middle..." << std::endl;
    test_vector.insert(1, words[1]);
    test_vector.insert(2, words[2]);

    std::cout << "Printing contents of vector..." << std::endl;
    for (int i = 0; i < test_vector.size(); ++i)
        std::cout << i << ": " << test_vector.at(i) << std::endl;

    std::cout << "Erasing 3rd element..." << std::endl;
    test_vector.erase(2);

    std::cout << "Printing contents of vector..." << std::endl;
    for (int i = 0; i < test_vector.size(); ++i)
        std::cout << i << ": " << test_vector.at(i) << std::endl;

    if (!test_vector.empty())
        std::cout << "Vector is not empty." << std::endl;

    std::cout << "Size: " << test_vector.size() << std::endl;

    return 0;
}
