cmake_minimum_required(VERSION 3.15)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(GeneticAlgorithm main.cpp tour.hpp city.hpp genetic_algorithm.cpp genetic_algorithm.hpp)