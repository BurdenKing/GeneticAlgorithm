//
// Created by Lawrence Zheng on 12/1/2019.
//

#include "genetic_algorithm.hpp"

void genetic_algorithm::shuffle_cities(tour &t) {
    shuffle(begin(t.cities), end(t.cities), mt19937(random_device()()));
}

double genetic_algorithm::get_distance_between_cities(city &a, city &b) {
    double x_dist = pow(a.getX() - b.getX() , 2);
    double y_dist = pow(a.getY() - b.getY() , 2);
    return sqrt(x_dist + y_dist);
}

double genetic_algorithm::get_tour_distance(tour &t) {
    double sum = 0;
    for(int i = 0; i < CITIIES_IN_TOUR - 1; i++) {
        sum += get_distance_between_cities(t.cities[i], t.cities[i + 1]);
    }
    return sum;
}

double genetic_algorithm::determine_fitness(tour &t) {
    return SCALAR / get_tour_distance(t);
}

tour genetic_algorithm::crossover(tour &a, tour &b) {
    int  random = rand() % CITIIES_IN_TOUR;
    tour child;

    for(int i = 0 ; i < random; i++){
        child.cities.push_back(a.cities[i]);
    }

    for(int j = 0; j < CITIIES_IN_TOUR; j++){
        if(random >= CITIIES_IN_TOUR)
            break;
        if(!(contains_city(child, b.cities[j]))){
            child.cities.push_back(b.cities[j]);
            random++;
        }
    }
    return child;
}

void genetic_algorithm::mutate(tour &a) {
    default_random_engine generator(time(0));
    uniform_real_distribution<double> realDistribution(0,1);

    for(int i = 0; i < CITIIES_IN_TOUR; i++){
        double r = realDistribution(generator);
        if(MUTATION_RATE >= r){
            if (CITIIES_IN_TOUR - 1 == i){
                city tmp = a.cities[i];
                a.cities[i] = a.cities[0];
                a.cities[0] = tmp;
            } else {
                city tmp = a.cities[i];
                a.cities[i] = a.cities[i + 1];
                a.cities[i + 1] = tmp;
            }
        }
    }
}

void genetic_algorithm::mutateAll(vector<tour> &p) {
    for (int i = 0; i <POPULATION_SIZE; i++){
        mutate(p[i]);
    }
}

bool genetic_algorithm::contains_city(tour &t, city &c) {
    for(unsigned int i = 0; i < t.cities.size(); i++){
        if(t.cities[i].getName() == c.getName() &&
            t.cities[i].getX() == c.getX() &&
            t.cities[i].getY() == c.getY()){
            return true;
        }
    }
    return false;
}

vector<tour> genetic_algorithm::generateTours() {
    vector<tour> population;
    for(int i = 0; i < POPULATION_SIZE; i++){
        tour tmp;
        for(int j = 0; j < CITIIES_IN_TOUR; j++){
            int x = rand() % (MAP_BOUNDARY + 1);
            int y = rand() % (MAP_BOUNDARY + 1);
            char n = (char) (j + 65);
            city c {n,x,y};
            tmp.cities.push_back(c);
        }
        shuffle_cities(tmp);
        tmp.setFitness(determine_fitness(tmp));
        population.push_back(tmp);
    }
    return population;
}

vector<tour> genetic_algorithm::getParent(vector<tour> &p) {
    vector<tour> parents;
    for (int i = 0; i < PARENT_POOL_SIZE ; i++) {
        int x = rand() % POPULATION_SIZE;
        parents.push_back(p[x]);
    }
    return parents;
}

vector<tour> genetic_algorithm::getCrossovers(vector<tour> &p) {
    vector<tour> crossovers;
    for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE ; i++) {

        vector<tour> parentGroup1 = getParent(p);
        vector<tour> parentGroup2 = getParent(p);

        moveEliteToFirst(parentGroup1);
        moveEliteToFirst(parentGroup2);

        tour parent1 = parentGroup1[0];
        tour parent2 = parentGroup2[0];
        tour childTour = crossover(parent1, parent2);

        childTour.setFitness(determine_fitness(childTour));
        crossovers.push_back(childTour);
    }
    return crossovers;
}

void genetic_algorithm::moveEliteToFirst(vector<tour> &p) {
    int elite = 0;
    for(unsigned int i = 0; i < p.size(); i++){
        if(p[elite].getFitness() < p[i].getFitness()){
            elite = i;
        }
    }

    if(0 != elite){
        tour tmp = p[0];
        p[0] = p[elite];
        p[elite] = tmp;
    }
}

void genetic_algorithm::toString(tour &t) {
    for(auto c : t.cities){
        cout << c.getName() << " ";
    }
    cout <<"|||| Fitness level: " << t.getFitness() << "  Distance: " << get_tour_distance(t) << endl;
}

void genetic_algorithm::genetic_driver(int num_of_cities, int size_of_population) {
    bool algoFinished = false;
    int iteration = 0;

    CITIIES_IN_TOUR = num_of_cities;
    POPULATION_SIZE = size_of_population;

    srand(time(0));

    vector<tour> population = generateTours();
    moveEliteToFirst(population);

    double base_dist = SCALAR / population[0].getFitness();
    double best_dist = base_dist;
    tour base = population[0];
    tour best = population[0];

    for (; iteration < ITERATIONS; iteration++) {
        vector<tour> crosses = getCrossovers(population);

        for (int j = NUMBER_OF_ELITES; j < POPULATION_SIZE; j++) {
            population[j] = crosses[j - NUMBER_OF_ELITES];
        }

        mutateAll(population);

        for (int k = 0; k < POPULATION_SIZE; k++) {
            population[k].setFitness(determine_fitness(population[k]));
        }

        moveEliteToFirst(population);

        double iter_dist = SCALAR / population[0].getFitness();


        cout << "|*******************************************************************|" << endl;
        cout << "Iteration Number: " << iteration << endl;
        cout << "Distance: " << iter_dist << endl;

        if (best_dist > iter_dist) {
            best_dist = iter_dist;
            best = population[0];
        }

        cout << "Best Distance: " << best_dist << endl;
        double improv = (base_dist - best_dist) / base_dist;
        cout << "Improvement Over Base: " << improv << endl;

        if (IMPROVEMENT_FACTOR < improv) {
            algoFinished = true;
            cout << "Algorithm finished......." << endl;
            break;
        }
    }

    cout << "|*******************************************************************|" << endl;
    cout << "Number of iterations: " << iteration + 1 << endl;
    cout << "Base Distance: " << base_dist << endl;
    cout << "Best Distance: " << best_dist << endl;

    if (algoFinished) {
        cout << "Improvement Achieved" << endl;
    } else {
        cout << "Improvement still needed" << endl;
    }

    cout << "|**********************Base Route***********************************|" << endl;
    toString(base);

    cout << "|**********************Best Route***********************************|" << endl;
    toString(best);

}