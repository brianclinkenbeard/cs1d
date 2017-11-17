#include "binarysearchtree.h"

/*
 * Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 4
 * This program will test a binary tree implemented with a linked list.
 * It will first perform the in-order, post-order, pre-order, breadth-first
 * traversals using the given data. In addition to the traversals, the
 * program will print out the binary tree by level, showing the parent-child
 * relationship for all of the nodes of the tree.
 */

int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 4\n"
              << "This program will test a binary tree implemented with a linked list.\n"
              << "It will first perform the in-order, post-order, pre-order, breadth-first\n"
              << "traversals using the given data. In addition to the traversals, the\n"
              << "program will print out the binary tree by level, showing the parent-child\n"
              << "relationship for all of the nodes of the tree.\n" << std::endl;

     int elems[14] = { 109, 18, 44, 88, 12, 24, 49, 7, 35, 55, 18, 19, 13, 1001 };

    bSearchTreeType tree;

    /* insert elements into the tree */
    std::cout << "Inserting: ";
    for (int i = 0; i < 14; ++i) {
        if (i != 0 && i != 14)
            std::cout << ", ";

        std::cout << elems[i];
        tree.insert(elems[i]);
    }
    std::cout << std::endl << std::endl;

    /* traversals */
    std::cout << "In order traversal: ";
    tree.inorderTraversal();
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    tree.postorderTraversal();
    std::cout << std::endl;

    std::cout << "Pre-order traversal: ";
    tree.preorderTraversal();
    std::cout << std::endl;

    std::cout << "Breadth-first traversal: ";
    tree.breadthfirstTraversal(false);
    std::cout << std::endl;

    std::cout << std::endl << "Breadth-first traversal by level (with relationships):" << std::endl;
    tree.breadthfirstTraversal(true);
    std::cout << std::endl;

    return 0;
}
