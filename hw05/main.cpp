#include <iostream>	/* cout */
#include <queue>	/* priority_queue */
#include <chrono>	/* milliseconds */
#include <thread>	/* sleep_for */
#include "patient.h"
#include "compare.h"
#include "listpriorityqueue.h"

/*
 * Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 5
 * This program will implement two priority queues to simulate an afternoon in an emergency room. It will
 * test one priority queue ADT as well as the STL priority queue with the given data and will assume the
 * priority queue is built at noon with one doctor on duty and each patient require 20 minutes of care.
 * The patient who waited the longest has the highest priority unless there is a life-threatening scenario.
 */

std::string print_time(int hr, int min)
{
    /* hour in 12h time */
    std::string string_hr;
    if (hr != 12)
        string_hr = std::to_string(hr % 12);
    else
        string_hr = std::to_string(hr);

    /* prepend 0 to minutes if needed */
    std::string string_min;
    if (min < 10)
        string_min = "0" + std::to_string(min);
    else
        string_min = std::to_string(min);

    return string_hr + ":" + string_min;
}

int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 3:00 PM | Assignment 5\n"
              << "This program will implement two priority queues to simulate an afternoon in an emergency room. It will\n"
              << "test one priority queue ADT as well as the STL priority queue with the given data and will assume the\n"
              << "priority queue is built at noon with one doctor on duty and each patient require 20 minutes of care.\n"
              << "The patient who waited the longest has the highest priority unless there is a life-threatening scenario.\n"
              << std::endl;

    ListPriorityQueue<Patient, Compare> adt_queue;

    Patient irene("Irene Ill", 6.0, false);
    Patient cathy("Cathy Coughing", 4.0, false);
    Patient alice("Alice Ailment", 2.0, false);
    Patient paula("Paula Pain", 5.0, false);
    Patient sid("Sid Sickly", 7.0, false);
    Patient sam("Sam Sneezing", 2.5, false);
    Patient tom("Tom Temperature", 1.0, false);

    adt_queue.insert(irene);
    adt_queue.insert(cathy);
    adt_queue.insert(alice);
    adt_queue.insert(paula);
    adt_queue.insert(sid);
    adt_queue.insert(sam);
    adt_queue.insert(tom);

    Patient bob("[Life Threatening] Bob Bleeding", 2.0, true);
    Patient frank("[Life Threatening] Frank Feelingbad", 1.0, true);

    // 24h time
    int hours = 12;
    int minutes = 0;

    int treatment = 0;
    int priority_treatment = 0;
    bool priority = false;

    /* priority queue ADT */
    std::cout << "Using author's priority queue ADT based on sorted std::list..." << std::endl;

    std::cout << adt_queue.min().getName() << " start time: " << print_time(hours, minutes) << std::endl;
    while (!adt_queue.empty() || hours < 15) {
        if (treatment == 20) {
            std::cout << adt_queue.min().getName() << " end time: " << print_time(hours, minutes) << std::endl;
            adt_queue.removeMin();

            if (!adt_queue.empty()) {
                std::cout << adt_queue.min().getName() << " start time: " << print_time(hours, minutes) << std::endl;

            treatment = 0;
            }
        }

        if (priority_treatment == 20) {
            std::cout << adt_queue.min().getName() << " end time: " << print_time(hours, minutes) << std::endl;
            adt_queue.removeMin();
            priority_treatment = 0;
            priority = false;
        }

        if (hours == 12 && minutes == 22) {
            adt_queue.insert(bob);
            std::cout << adt_queue.min().getName() << " start time: " << print_time(hours, minutes) << std::endl;
            priority = true;
        }

        if (hours == 14 && minutes == 55) {
            adt_queue.insert(frank);
            std::cout << adt_queue.min().getName() << " start time: " << print_time(hours, minutes) << std::endl;
            priority = true;
        }

        // sleep for 10ms
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // time keeping
        minutes++;

        if (minutes == 60) {
            hours++;
            minutes = 0;
        }

        // track treatment time
        if (!priority) {
            treatment++;
        } else {
            priority_treatment++;
        }
    }

    std::priority_queue<Patient, std::vector<Patient>, Compare> stl_queue;

    stl_queue.push(irene);
    stl_queue.push(cathy);
    stl_queue.push(alice);
    stl_queue.push(paula);
    stl_queue.push(sid);
    stl_queue.push(sam);
    stl_queue.push(tom);

    hours = 12;
    minutes = 0;

    treatment = 0;
    priority_treatment = 0;
    priority = false;

    std::cout << std::endl;

    // std::priority_queue
    std::cout << "Using std::priority_queue..." << std::endl;

    std::cout << stl_queue.top().getName() << " start time: " << print_time(hours, minutes) << std::endl;
    while (!stl_queue.empty() || hours < 15) {
        if (treatment == 20) {
            // dismiss patient
            std::cout << stl_queue.top().getName() << " end time: " << print_time(hours, minutes) << std::endl;
            stl_queue.pop();

            if (!stl_queue.empty()) {
                std::cout << stl_queue.top().getName() << " start time: " << print_time(hours, minutes) << std::endl;

            treatment = 0;
            }
        }

        if (priority_treatment == 20) {
            std::cout << stl_queue.top().getName() << " end time: " << print_time(hours, minutes) << std::endl;
            stl_queue.pop();
            priority_treatment = 0;
            priority = false;
        }

        if (hours == 12 && minutes == 22) {
            stl_queue.push(bob);
            std::cout << stl_queue.top().getName() << " start time: " << print_time(hours, minutes) << std::endl;
            priority = true;
        }

        if (hours == 14 && minutes == 55) {
            stl_queue.push(frank);
            std::cout << stl_queue.top().getName() << " start time: " << print_time(hours, minutes) << std::endl;
            priority = true;
        }

        // sleep for 10ms (represents one minute)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // time keeping
        minutes++;

        if (minutes == 60) {
            hours++;
            minutes = 0;
        }

        // track treatment time
        if (!priority) {
            treatment++;
        } else {
            priority_treatment++;
        }
    }

    return 0;
}
