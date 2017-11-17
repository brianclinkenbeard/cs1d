#include "citymap.h"

CityMap::CityMap()
{
    buckets.resize(29, { -1 , "" });
}

void CityMap::double_hash(City city) {
    // produce debug output when true
    bool verbose = false;
    if (verbose)
        std::cout << city.city_name << std::endl;

    int first = city.key % 29;
    if (verbose)
        std::cout << "h(k) = " << city.key << " % 29 = " << first << std::endl;

    if (buckets.at(first).key == -1 || buckets.at(first).key == city.key) {
        buckets.at(first) = city;
    } else {
        int prime = 17 - (city.key % 17);
        if (verbose)
            std::cout << "h'(k) = 17 - " << city.key << " % 17 = " << prime << std::endl;

        // increment until an empty bucket is reached
        for (unsigned int j = 0; j < buckets.size(); ++j) {
            if (buckets.at((first + (j * prime)) % 29).key == -1 || buckets.at((first + (j * prime)) % 29).key == city.key) {
                buckets.at((first + (j * prime)) % 29) = city;
                if (verbose)
                    std::cout << "Final index = " << (first + (j * prime)) % 29 << std::endl;
                break;
            }
            if (verbose)
                std::cout << "Index: " << ((first + (j*prime)) % 29) << std::endl;
        }
    }
}

void CityMap::quadratic_hash(City city) {
    int first = city.key % 29;
    if (buckets.at(first).key == -1 || buckets.at(first).key == city.key) {
        buckets.at(first) = city;
    } else {
        for (int j = 0; j < 29; ++j) {
            int index = (first + (j * j)) % 29;
            // loop until empty bucket
            if (buckets.at(index).key == -1) {
                buckets.at(index) = city;
                return;
            }
        }
    }
}

void CityMap::remove_key(int key) {
    std::cout << "Removing key " << key << "..." << std::endl;
    for (unsigned int i = 0; i < buckets.size(); ++i) {
        if (buckets.at(i).key == key) {
            // replace with "empty" key
            buckets.at(i) = { -1 , "" };
            return;
        }
    }

    std::cout << "Failed to remove key." << std::endl;
}

void CityMap::clear() {
    buckets.clear();
    buckets.resize(29, { -1 , "" });
}

void CityMap::print() {
    for (unsigned int i = 0; i < buckets.size(); ++i) {
        // indicate empty buckets
        std::string city;
        if (buckets.at(i).key == -1)
            city = "Empty";
        else
            city = std::to_string(buckets.at(i).key) + " " + buckets.at(i).city_name;

        std::cout << i << ": " << city << std::endl;
    }
}
