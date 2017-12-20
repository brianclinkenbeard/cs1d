#include <vector>
#include <iostream>
#include <iterator>
#include <chrono>

enum pivot_type { FIRST, MIDDLE, RANDOM };
void quicksort(std::vector<int> &elements, pivot_type pv_type, int left, int right)
{
    int i = left;
    int j = right;
    int pivot, mid;
    switch (pv_type) {
    case FIRST:
        pivot = elements.at(left) + 1;
        break;
    case MIDDLE:
        mid = (left + right) / 2;
        pivot = elements.at(mid);
        break;
    case RANDOM:
        pivot = elements.at(rand() % elements.size());
        // fall through
    }

    while(left < j || i < right) {
        while (elements.at(i) < pivot && i < j) {
            //std::cout << "i" << i << std::endl;
            i++;
        }
        while (elements.at(j) > pivot && j > i) {
            //std::cout << "j" << j << std::endl;
            j--;
        }
         if (i <= j) {
            std::swap(elements.at(i), elements.at(j));
            i++;
            j--;
        }
        else {
            if (left < j)
                quicksort(elements, pv_type, left, j);

            if (i < right)
                quicksort(elements, pv_type, i, right);

            return;
        }
    }
}

int main()
{
    for (int i = 0; i < 3; ++i) {
        std::vector<int> example;
        switch (i) {
        case 0:
            std::cout << "Using already ordered set and " << std::endl;
            example = { 2, 4, 6, 8, 10, 12, 14, 16, 18 };
            break;
        case 1:
            std::cout << "Using reverse ordered set and " << std::endl;
            example = { 19, 17, 15, 13, 11, 9, 7, 5, 3, 1 };
            break;
        case 2:
            std::cout << "Using randomly ordered set and" << std::endl;
            for (int i = 0; i < 25; ++i)
                example.push_back(rand() % 100);
            // fall through
        }

        for (int j = 0; j < 3; ++j) {
            pivot_type type = static_cast<pivot_type>(j);

            switch (j) {
            case 0:
                std::cout << "first element as pivot:" << std::endl;
                break;
            case 1:
                std::cout << "middle element as pivot:" << std::endl;
                break;
            case 2:
                std::cout << "random element as pivot:" << std::endl;
            }

            std::cout << "Before:\t";
            std::copy(example.begin(), example.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;

            auto start = std::chrono::system_clock::now();
            quicksort(example, type, 0, example.size() - 1);
            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);

            std::cout << "elapsed time: " << std::fixed << elapsed_seconds.count() << "s\n";

            std::cout << "After:\t";
            std::copy(example.begin(), example.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl << std::endl;
        }

    }
}
