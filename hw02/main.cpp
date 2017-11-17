/*
 * Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 2
 */

#include "header.h"
#include "singlestack.h"
#include "circularqueue.h"
#include "dequelist.h"

bool matches(std::string expr);

int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 2" << std::endl;
    std::cout << "This program will test various implementations of stacks and queues using a set of given data.\n"
              << "It will print this data before and after being manipulated. The program will also later test\n"
              << "a set of given mathmatical expressions and determine their validity of their parenthesis use."
              << std::endl << std::endl;

    std::string names[6] = { "Eric", "Jennifer", "JoAnn", "Mark", "Alan", "Rick" };
    double doubles[7] = { 44.44, 888.55, 88.88, 123.123, 8.445, 983.3, 1.2 };

    // A.
    std::stack<std::string> names_a;
    std::stack<double> doubles_a;

    // populate
    for (int i = 0; i < 6; ++i)
        names_a.push(names[i]);
    for (int i = 0; i < 7; ++i)
        doubles_a.push(doubles[i]);

    // A. print
    std::cout << "A. Print stanks using STL <stack>\nNames:" << std::endl;
    for (std::stack<std::string> print = names_a; !print.empty(); print.pop())
        std::cout << print.top() << std::endl;
    std::cout << "Doubles:" << std::endl;
    for (std::stack<double> print = doubles_a; !print.empty(); print.pop())
        std::cout << print.top() << std::endl;
    std::cout << std::endl;

    // pop Alan and 123.123
    while (names_a.top() != "Alan")
        names_a.pop();
    names_a.pop();

    while (doubles_a.top() != 123.123)
        doubles_a.pop();
    doubles_a.pop();

    // B. print
    std::cout << "B. Print remaining stacks\nNames:" << std::endl;
    for (std::stack<std::string> print = names_a; !print.empty(); print.pop())
        std::cout << print.top() << std::endl;
    std::cout << "Doubles:" << std::endl;
    for (std::stack<double> print = doubles_a; !print.empty(); print.pop())
        std::cout << print.top() << std::endl;
    std::cout << std::endl;

    // C.
    SingleStack<std::string> names_c;
    SingleStack<double> doubles_c;

    // populate
    for (int i = 0; i < 6; ++i)
        names_c.push(names[i]);
    for (int i = 0; i < 7; ++i)
        doubles_c.push(doubles[i]);

    // C. print
    std::cout << "C. Print stacks using singly-linked list\nNames:" << std::endl;
    names_c.print();
    std::cout << "Doubles:" << std::endl;
    doubles_c.print();
    std::cout << std::endl;

    // pop Alan and 123.123
    while (names_c.get_top() != "Alan")
        names_c.pop();
    names_c.pop();

    while (doubles_c.get_top() != 123.123)
        doubles_c.pop();
    doubles_c.pop();

    // D. print
    std::cout << "D. Print remaining stacks using singly-linked list\nNames:" << std::endl;
    names_c.print();
    std::cout << "Doubles:" << std::endl;
    doubles_c.print();
    std::cout << std::endl;

    // E.
    CircularQueue<std::string> names_e;
    CircularQueue<double> doubles_e;

    // populate
    for (int i = 0; i < 6; ++i)
        names_e.enqueue(names[i]);
    for (int i = 0; i < 7; ++i)
        doubles_e.enqueue(doubles[i]);

    // E. print
    std::cout << "E. Print queue using circular arrays\nNames:" << std::endl;
    names_e.print();
    std::cout << "Doubles:" << std::endl;
    doubles_e.print();
    std::cout << std::endl;

    // dequeue Alan and 123.123
    while (names_e.get_front() != "Alan")
        names_e.dequeue();
    names_e.dequeue();

    while (doubles_e.get_front() != 123.123)
        doubles_e.dequeue();
    doubles_e.dequeue();

    // F. print
    std::cout << "F. Print remaining queues using circular arrays\nNames:" << std::endl;
    names_e.print();
    std::cout << "Doubles:" << std::endl;
    doubles_e.print();
    std::cout << std::endl;

    // G.
    DequeList<std::string> names_g;
    DequeList<double> doubles_g;

    // populate
    for (int i = 0; i < 6; ++i)
        names_g.insert_front(names[i]);
    for (int i = 0; i < 7; ++i)
        doubles_g.insert_front(doubles[i]);

    // G. print
    std::cout << "G. Print deques using doubly-linked lists\nNames:" << std::endl;
    names_g.print();
    std::cout << "Doubles:" << std::endl;
    doubles_g.print();
    std::cout << std::endl;

    // dequeue Alan and 123.123
    while (names_g.front() != "Alan")
        names_g.remove_front();
    names_g.remove_front();

    while (doubles_g.front() != 123.123)
        doubles_g.remove_front();
    doubles_g.remove_front();

    // H. print
    std::cout << "H. Print remaining deques using doubly-linked lists\nNames:" << std::endl;
    names_g.print();
    std::cout << "Doubles:" << std::endl;
    doubles_g.print();
    std::cout << std::endl;

    // I.
    std::cout << "I. Testing parenthesis algorithm:" << std::endl;
    std::string exprs[7] = { "(2x - 8) (12x + 6)",
                            "{2x + 5} (6x+4)}",
                            "(((4x+8) - x[4x+3])))",
                            "[(5x - 5) - 4x[6x + 2]]",
                            "{{8x+5) - 5x[9x+3]})",
                            "{(8x+5) - 6x[9x+3]]",
                            "(12x + 6} (2x - 4)" };
    for (int i = 0; i < 7; ++i) {
        std::cout << exprs[i] << " - ";
        std::cout << (matches(exprs[i]) ? "valid" : "invalid");
        std::cout << std::endl;
    }

    return 0;
}

bool bracket_match(char open, char close)
{
    if (open == '(' && close == ')')
        return true;
    else if (open == '{' && close == '}')
        return true;
    else if (open == '[' && close == ']')
        return true;
    else
        return false;
}

bool matches(std::string expr)
{
    std::stack<char> paren_stack;

    for (unsigned int i = 0; i < expr.length(); ++i) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
            paren_stack.push(expr[i]);
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']')
            if (!paren_stack.empty() && bracket_match(paren_stack.top(), expr[i]))
                paren_stack.pop();
    }

    return paren_stack.empty();
}
