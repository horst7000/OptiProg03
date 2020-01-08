#ifndef CPP_FOOTBALLBETTINGGAMEALGORITHM_H
#define CPP_FOOTBALLBETTINGGAMEALGORITHM_H

#include <list>
#include "../dataStructures/Matchday.h"
#include "../dataStructures/FootballBettingGameSolution.h"

class FootballBettingGameAlgorithm {

private:

public:
    /**
     * Constructor for FootballBettingGameAlgorithmImpl
     *
     * @param matchdayList the list of matchdays ordered by matchday number
     */
    FootballBettingGameAlgorithm();

    /**
     * Calculates the optimal solution for the football betting game.
     *
     * @return the optimal solution for the football betting game
     */
    FootballBettingGameSolution* calculateSolution(std::list<Matchday>& matchdayList);
};


#endif //CPP_FOOTBALLBETTINGGAMEALGORITHM_H
