//
// Created by Lawrence Zheng on 12/1/2019.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

using namespace std;

/*
 * Class represents cities for Travelling salesman problem.
 */
class city {

private:
    char  name;
    int x;
    int y;

public:
    //Destructor
    ~city() = default;

    //Constructors
    //Default
    city() = default;

    /**
     * Constructor
     * @param n name of the city.
     * @param x x-coordinate.
     * @param y y-coordinate.
     */
    city(char n, int x, int y) : name(n) {
        if(x < 0 || x > 1000){
            throw "X must be an integer between 0 and 1000";
        }
        if(y < 0 || y > 1000){
            throw "Y must be an integer between 0 and 1000";
        }
        this->x = x;
        this->y = y;
    }

    //Getters

    /**
     * name getter.
     * @return name.
     */
    char getName(){
        return name;
    }

    /**
     * x getter.
     * @return x-coordinate.
     */
    int getX(){
        return x;
    }

    /**
     * y getter
     * @return y-coordinate.
     */
    int getY(){
        return y;
    }
};


#endif //GENETICALGORITHM_CITY_HPP
