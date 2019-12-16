//
// Created by justin on 11/27/19.
//

#ifndef SIMPLE_EXAMPLE_GALAXY_H
#define SIMPLE_EXAMPLE_GALAXY_H
#include "Planet.h"
#include <vector>
#include<bits/stdc++.h>

class Galaxy {
    std::vector<Planet> planetList;
public:
    Galaxy(std::string filename);
    //Takes in a filename and build a list of planets with adjacencies
    unsigned int size();
    //The number of planets currently contained in the galaxy
    Planet* findByName(std::string planetName);
    //Returns the planet object with the associated name
    std::vector<Planet *> shortestPath(Planet * start, Planet * dest);
    void findAdjacents();
    double pathDistance(Planet * start, Planet * dest);
    int minDistance(double *distance, bool* finished, int size);

    double distBetPlanets(Planet &a, Planet &b);
};


#endif //SIMPLE_EXAMPLE_GALAXY_H
