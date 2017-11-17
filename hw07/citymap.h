#ifndef CITYMAP_H
#define CITYMAP_H

#include <iostream>
#include <string>
#include <vector>

struct City {
    int key;
    std::string city_name;
};


class CityMap {
public:
    CityMap();
    void double_hash(City);
    void quadratic_hash(City);
    void remove_key(int);
    void clear();
    void print();
private:
    std::vector<City> buckets;
};

#endif // CITYMAP_H
