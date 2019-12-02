//
// Created by Lawrence Zheng on 12/1/2019.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include "city.hpp"
#include <vector>


/*
 * Class represents tour in travelling salesman problem.
 */
class tour {

private:
    /**
     * Fitness of the tour.
     */
    double fitness;

public:
    /**
     * List of all cities in the tour.
     */
    vector<city> cities;

    //Default Constructor
    tour() = default;

    //Destructor
    ~tour() = default;

    /**
     * Getter for fitness.
     * @return double as fitness.
     */
    double getFitness(){
        return this->fitness;
    }

    /**
     * Setter for fitness.
     * @param f as the fitness.
     */
    void setFitness(double f){
        this->fitness = f;
    }

};


#endif //GENETICALGORITHM_TOUR_HPP
