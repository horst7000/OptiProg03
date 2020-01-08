#ifndef GRAPH_ALGO_FOOTBALLBETTINGGAMEPARSER_H
#define GRAPH_ALGO_FOOTBALLBETTINGGAMEPARSER_H

#include <list>

#include "../dataStructures/Matchday.h"

class FootballBettingGameParser {

private:

public:

/**
 * Returns a list of matchdays ordered by the matchday number.
 *
 * @return the matchdays
 */
std::list<Matchday>* parseInstance(std::string &path);

};


#endif //GRAPH_ALGO_FOOTBALLBETTINGGAMEPARSER_H
