//
// Created by justin on 11/27/19.
//

#include "Galaxy.h"
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <algorithm>

Galaxy::Galaxy(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file,line)){
        std::stringstream stream(line);
        std::string planet;
        stream >> planet;
        long x,y,z;
        stream >> x >> y >> z;
        planetList.push_back(Planet(planet, x,y,z));
    }
    findAdjacents();
}
double Galaxy::distBetPlanets(Planet& a, Planet& b){
    return sqrt(  (a.getXCoor() - b.getXCoor()) * (a.getXCoor() - b.getXCoor())
                  + (a.getYCoor() - b.getYCoor()) * (a.getYCoor() - b.getYCoor())
                  + (a.getZCoor() - b.getZCoor()) * (a.getZCoor() - b.getZCoor()));
}

void Galaxy::findAdjacents() {
    for(auto& planet : planetList){
        std::map<double, Planet*> distances;
        for(auto& temp : planetList){
            double distance = distBetPlanets(planet, temp);
            distances.insert(std::pair<double, Planet*>(distance, &temp));
        }
        auto it = distances.begin(); ++it;
        planet.adjList[it->first] = it->second;
        ++it;
        planet.adjList[it->first] = it->second;
        ++it;
        planet.adjList[it->first] = it->second;
        ++it;
        planet.adjList[it->first] = it->second;
    }
}

unsigned int Galaxy::size() {
    return planetList.size();
}

Planet* Galaxy::findByName(std::string planetName){
    for(unsigned int i = 0; i < planetList.size(); i++){
        if(planetList.at(i).getName() == planetName){
            return &planetList.at(i);
        }
    }
    return nullptr;
}

std::vector<Planet *> Galaxy::shortestPath(Planet *start, Planet *dest) {
    //shitty hack
    if(start == dest){
        std::vector<Planet*> retval{start};
        return retval;
    }

    int size = planetList.size();
    double distance[size];
    bool finished[size];
    Planet* optimalPrev[size];
    std::map<Planet*, int> planetToIndex;
    for(int i = 0; i < size; i++){
        planetToIndex[&planetList[i]] = i;
    }
    for(int i = 0; i < size; i++){
        distance[i] = LDBL_MAX;
        optimalPrev[i] = nullptr;
        finished[i] = false;
    }

//    auto source = std::find(planetList.begin(), planetList.end(), *start);
    distance[planetToIndex[start]] = 0;
    for(int i = 0; i < size-1; i++){
        int minDist = minDistance(distance, finished, size);
        finished[minDist] = true;

        for(auto const& [distToAdj, adjPlanet] : planetList[minDist].adjList){
            int indexOfThisAdj = planetToIndex[adjPlanet];
            if(!finished[indexOfThisAdj] &&  distance[minDist] != LDBL_MAX &&
                distance[minDist] + distToAdj < distance[indexOfThisAdj]){
                distance[indexOfThisAdj] = distance[minDist] + distToAdj;
                optimalPrev[indexOfThisAdj] = &planetList[minDist];
            }
        }
    }

    std::vector<Planet *> retval;
    int destIndex = planetToIndex[dest];
    for(Planet* temp = dest; optimalPrev[destIndex] != nullptr; temp = optimalPrev[destIndex]){
        retval.push_back(temp);
        destIndex = planetToIndex[temp];
    }

    std::reverse(retval.begin(), retval.end());
    return retval;
}

int Galaxy::minDistance(double* distance, bool* finished, int size){
    double min = DBL_MAX;
    int minIdx;
    for(int i = 0; i < size; i++){
        if(!finished[i] && distance[i] <= min) {
            min = distance[i];
            minIdx = i;
        }
    }
    return minIdx;
}

double Galaxy::pathDistance(Planet *start, Planet *dest) {
    auto path = shortestPath(start, dest);
    if(path.empty()) return LDBL_MAX;
    if(path.size() == 1) return 0;
    else{
        double sum = 0;
        for(unsigned int i = 0; i < path.size()-1; i++){
            sum += distBetPlanets(*path[i], *path[i+1]);
        }
        return sum;
    }
}
//int main(){
//    Galaxy test("planetsB.dat");
//    Planet* startc = test.findByName("CMab");
//    Planet* destc = test.findByName("HD116029b");
//    auto vect = test.shortestPath(startc,destc);
//}
//int main(){
//    for(int i = 3; i <= 13; i++){
//        std::cout << "-DTEST" << i << " ";
//    }
//}
