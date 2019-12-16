//
// Created by justin on 11/27/19.
//

#include "Planet.h"

Planet::Planet(std::string planetName, long xCoor, long yCoor, long zCoor){
    this->planetName = planetName;
    this->xCoor = xCoor;
    this->yCoor = yCoor;
    this->zCoor = zCoor;
}

std::list<Planet *> Planet::getAdjacent() {
    std::list<Planet *>retval;
    for(auto temp : adjList){
        retval.push_back(temp.second);
    }
    return retval;
}
