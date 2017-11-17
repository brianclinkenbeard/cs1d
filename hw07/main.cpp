#include "citymap.h"

int main()
{
    std::cout << "Brian Clinkenbeard | CS1D MW 1:00 PM | Assignment 7\n"
              << "This program will first store cities and their respective keys\n"
              << "in a vector. It will follow by double hashing each city to a map\n"
              << "Finally, it will use a quadratic hashing algorithm on the same\n"
              << "cities to store them to a map.\n"
              << std::endl;

    std::vector<City> cities = {
        { 18, "Laguna Niguel" }, { 41, "Mission Viejo" }, { 22, "San Clemente" }, { 44, "Irvine" }, { 58, "Lake Forest" },
        { 32, "San Diego" }, { 49, "Anaheim" }, { 31, "Los Angeles" }, { 17, "Orange" }, { 72, "Palm Springs" },
        { 41, "Riverside" }, { 19, "Brea" }, { 60, "Santa Ana" }, { 35, "Tustin" }, { 103, "Oceanside" }, { 11, "La Jolla" },
        { 18, "Del Mar" }, { 22, "Aliso Viejo" }, { 49, "Laguna Beach" }, { 42, "Vista" }, { 49, "San Diego" },
        { 99, "San Juan" }, { 29, "Dana Point" }, { 88, "El Segundo" }, { 41, "San Clemente" }, { 62, "Laguna Hills" }
    };

    CityMap map;

    std::cout << "Part 1: Double hashing using map of vectors" << std::endl;
    // double hash cities to map
    std::cout << "Adding cities..." << std::endl;
    for (unsigned int i = 0; i < cities.size(); ++i) {
        if (i == 4)
            map.remove_key(41);
        if (i == 7)
            map.remove_key(58);
        if (i == 11)
            map.remove_key(73);
        if (i == 19)
            map.remove_key(41);
        map.double_hash(cities.at(i));
    }

    map.print();

    // empty map for reuse with quadratic hashing
    map.clear();

    std::cout << std::endl << "Part 2: Quadratic hashing using map of vectors" << std::endl;
    // quadratic hash cities to the map
    std::cout << "Adding cities..." << std::endl;
    for (unsigned int i = 0; i < cities.size(); ++i) {
        if (i == 4)
            map.remove_key(41);
        if (i == 7)
            map.remove_key(58);
        if (i == 11)
            map.remove_key(73);
        if (i == 19)
            map.remove_key(41);
        map.quadratic_hash(cities.at(i));
    }

    map.print();

    return 0;
}
