#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <chrono>

enum pivot_type { FIRST, MIDDLE, RANDOM };

static int count = 0;

// https://codereview.stackexchange.com/a/77788
int partition(std::vector<int> &elements, pivot_type pt, const int left, const int right) {

    int pos, pivot;
    switch (pt) {
    case FIRST:
        pos = left;
        break;
    case MIDDLE:
        pos = ((right - left) / 2) + left;
        break;
    case RANDOM:
        pos = (rand() % (right - left)) + left;
        // fall through
    }
    pivot = elements.at(pos);
    count++;

    // move the pivot value to the front
    std::swap(elements.at(pos), elements.at(left));
    count += 3;

    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && elements[i] <= pivot) {
            count++;
            i++;
        }

        while(i <= j && elements[j] > pivot) {
            count++;
            j--;
        }

        if (i < j) {
            std::swap(elements[i], elements[j]);
            count += 3;
        }
    }
    std::swap(elements[i - 1], elements[left]);
    count += 3;

    return i - 1;
}

static int quicksort(std::vector<int> &arr, pivot_type pt, const int left, const int right) {
    count++;
    if (left >= right) {
        return count;
    }

    int part = partition(arr, pt, left, right);

    quicksort(arr, pt, left, part - 1);
    quicksort(arr, pt, part + 1, right);
}

int main()
{
    std::cout << "PART ONE:" << std::endl;
    for (int i = 0; i < 9; ++i) {
        std::vector<int> base;

        if (i == 0)
            std::cout << "1. Already ordered:" << std::endl;
        else if (i == 3)
            std::cout << "2. Reverse ordered:" << std::endl;
        else if (i == 6)
            std::cout << "3. Random ordered:" << std::endl;

        // generate numbers before ordering
        int size;
        switch (i % 3) {
        case 0:
            size = 5000;
            break;
        case 1:
            size = 10000;
            break;
        case 2:
            size = 50000;
            // fall through
        }
        std::cout << "Size: " << size << std::endl;

        for (int i = 0; i < size; ++i)
            base.push_back(rand() % 100000);

        if (i < 3)
            std::sort(base.begin(), base.end());
        else if (i < 6)
            std::sort(base.rbegin(), base.rend());

        std::cout << "Before:\t";
        std::copy(base.begin(), base.begin() + 5, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;

        std::vector<int> vec;
        for (int j = 0; j < 3; ++j) {
            pivot_type type = static_cast<pivot_type>(j);

            switch (j) {
            case 0:
                std::cout << "First element as pivot:" << std::endl;
                break;
            case 1:
                std::cout << "Middle element as pivot:" << std::endl;
                break;
            case 2:
                std::cout << "Random element as pivot:" << std::endl;
            }

            vec = base;

            auto start = std::chrono::system_clock::now();
            // sort
            std::cout << "Count: " << quicksort(vec, type, 0, vec.size() - 1) << std::endl;
            // reset counter
            count = 0;
            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;
            std::cout << "elapsed time: " << std::fixed << elapsed_seconds.count() << "s\n";
        }
        std::cout << "After:\t";
        std::copy(vec.begin(), vec.begin() + 5, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl << std::endl;
    }
}
