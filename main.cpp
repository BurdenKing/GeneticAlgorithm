#include <iostream>
#include "genetic_algorithm.hpp"

int main() {
    int cities, population;
    genetic_algorithm driver;
    cout << "How many cities in the tour?" << endl;
    cin >> cities;
    cout << "How many candidate tours?" << endl;
    cin >> population;

    driver.genetic_driver(cities, population);
    return 0;
}