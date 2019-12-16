//
// Created by justin on 11/27/19.
//

#ifndef SIMPLE_EXAMPLE_PLANET_H
#define SIMPLE_EXAMPLE_PLANET_H
#include <string>
#include <list>
#include <map>

class Planet {
    std::string planetName;
    long xCoor, yCoor, zCoor;
public:
    std::map<double, Planet*>adjList;
    Planet(std::string planetName, long xCoor, long yCoor, long zCoor);
    std::string getName(){return planetName;}
    long getXCoor(){return xCoor;}
    long getYCoor(){return yCoor;}
    long getZCoor(){return zCoor;}
    std::list<Planet*> getAdjacent();
};


#endif //SIMPLE_EXAMPLE_PLANET_H
