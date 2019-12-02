//
// Created by Lawrence Zheng on 12/1/2019.
//

#ifndef GENETICALGORITHM_GENETIC_ALGORITHM_HPP
#define GENETICALGORITHM_GENETIC_ALGORITHM_HPP

#include<random>
#include<iostream>
#include<iomanip>
#include<algorithm>

#include"city.hpp"
#include"tour.hpp"


class genetic_algorithm {

private:

    //Total number of cities in a tour.
    int CITIIES_IN_TOUR;

    //Total number of candidate tours.
    int POPULATION_SIZE;

    //The minimum number of times the algorithm should iterate.
    static constexpr int ITERATIONS = 1000;

    //The largest legal coordinate
    static constexpr int MAP_BOUNDARY = 1000;

    /*
     * The number of members randomly selected from the population whenchoosing a parent,
     * from which the fittest is made a ’parent'.
     */
    static constexpr int PARENT_POOL_SIZE = 5;

    //Mutation rate.
    static constexpr double MUTATION_RATE = 0.15;

    //Number of elite tour.
    static constexpr int NUMBER_OF_ELITES = 1;

    /*
     *  percentage that indicates what percent the new elite fitness
     *  needs toimprove over the base distance before exiting the algorithm loop
     */
    static constexpr double IMPROVEMENT_FACTOR = 0.15;

    //Scalar.
    static constexpr double SCALAR = 10000.0;


    /**
     * Shuffle all cities in a tour.
     * @param t a tour.
     */
    void shuffle_cities(tour &t);

    /**
     * Calculates the distance between two cities.
     * @param a city.
     * @param b city.
     * @return double as the distance between a and b.
     */
    double get_distance_between_cities(city &a, city &b);


    /**
     * Calculates the total distance of a tour.
     * @param t a tour.
     * @return double as the total distance.
     */
    double get_tour_distance(tour &t);

    /**
     * Detemines the fitness of a tour.
     * @param t a tour.
     * @return double as the fitness.
     */
    double determine_fitness(tour &t);

    /**
     * Generates a new tour from parents.
     * @param a tour
     * @param b tour
     * @return new tour.
     */
    tour crossover(tour &a, tour &b);

    /**
     * Perform mutation on one tour.
     * @param a tour.
     */
    void mutate(tour &a);


    /**
     * Mutates the whole population.
     * @param p list of all tours.
     */
    void mutateAll(vector<tour> &p);
    /**
     * Determine if a tour contains specific city.
     * @param t tour
     * @param c city
     * @return true if the tour contains the city, otherwise false.
     */
    bool contains_city(tour &t, city &c);

    /**
     * Generate list of tours.
     * @return a list of tours.
     */
    vector<tour> generateTours();

    /**
     * Find the parent group.
     * @param p a list of tours.
     * @return a list of tours.
     */
    vector<tour> getParent(vector<tour> &p);

    /**
     * Find all crossovers.
     * @param p a list of tours.
     * @return a list of tours.
     */
    vector<tour> getCrossovers(vector<tour> &p);

    /**
     * Move elite tour to the first of the list.
     * @param p  a list of tours.
     */
    void moveEliteToFirst(vector<tour> &p);

    /**
     * Prints out the tour.
     * @param t  a tour.
     */
    void toString(tour &t);

public:
    //Default constructor
    genetic_algorithm() = default;

    /**
     * Applies the algorithm after prompting user.
     * @param num_of_cities  number of cities in the problem.
     * @param size_of_population  size of the population.
     */
    void genetic_driver(int num_of_cities, int size_of_population);
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
