#ifndef CPP_FOOTBALLBETTINGGAMESOLUTION_H
#define CPP_FOOTBALLBETTINGGAMESOLUTION_H


#include <unordered_map>
#include "FootballTeam.h"
#include "Matchday.h"

class FootballBettingGameSolution {
    // TODO implement your data structure for al football betting game solution here

private:
    std::map<FootballTeam, Matchday*>* solutionMapPtr;

public:
    FootballBettingGameSolution(std::map<FootballTeam, Matchday*>* mapPtr) : solutionMapPtr(mapPtr) {}

    /**
     * Returns mapping from football team to matchday.
     *
     * @return the mapping from football team to matchday
     */
    std::map<FootballTeam, Matchday*>* getSolution();
};


#endif //CPP_FOOTBALLBETTINGGAMESOLUTION_H
