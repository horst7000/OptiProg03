#include "FootballBettingGameAlgorithm.h"
#include <lemon/lgf_reader.h>

using namespace lemon;


/**
 * Constructor for FootballBettingGameAlgorithmImpl
 *
 * @param matchdayList the list of matchdays ordered by matchday number
 */
FootballBettingGameAlgorithm::FootballBettingGameAlgorithm() {}

ListGraph::Node FootballBettingGameAlgorithm::nodeFromTeam(FootballTeam team) {
    return graph.nodeFromId(teamToLabel[team]-1);
}

/**
 * Calculates the optimal solution for the football betting game.
 *
 * @return the optimal solution for the football betting game
 */
FootballBettingGameSolution* FootballBettingGameAlgorithm::calculateSolution(std::list<Matchday>& matchdayList) {
    ListGraph::NodeMap<int> label(graph);
    ListGraph::EdgeMap<int> weight(graph);
    
    auto day1 = matchdayList.front().getMatches();
    int labelCtr = 1;
    for(auto & pp : day1) {
        auto n = graph.addNode(); // Team Knoten
        label[n] = labelCtr;
        teamToLabel[pp.first.first] = labelCtr;
        labelToTeam[labelCtr]       = &pp.first.first;
        labelCtr++;  

        n = graph.addNode(); // Team Knoten
        label[n] = labelCtr;
        teamToLabel[pp.first.second] = labelCtr;
        labelToTeam[labelCtr]        = &pp.first.second;
        labelCtr++;  
    }


    for(auto & md : matchdayList) {
        auto n = graph.addNode(); // Spieltag Knoten
        label[n] = labelCtr; // label 19-35

        auto matches = md.getMatches();
        for(auto & pp : matches) {
            auto team1 = graph.addEdge(n,nodeFromTeam(pp.first.first));
            auto team2 = graph.addEdge(n,nodeFromTeam(pp.first.second));
            
            // Punkte aus Spiel -> Kantengewicht
            // pp.second.first = Tore von Team 1
            if(pp.second.first > pp.second.second) {
                weight[team1] = 3;
                weight[team2] = 0;
            } else if(pp.second.first < pp.second.second) {
                weight[team1] = 0;
                weight[team2] = 3;
            } else {
                weight[team1] = 1;
                weight[team2] = 1;
            }
        }
    }

    BipartiteMatchingAlgorithm algo;
    auto matchingMap = algo.getMatching(graph,weight);
    
    auto solutionMapPtr = new std::map<FootballTeam, Matchday*>();
    for(auto & md : matchdayList)
        (*solutionMapPtr)[*labelToTeam[matchingMap->at(md.getNumber()+18)]] = &md; // Spieltage haben label 19-35
        
    
    FootballBettingGameSolution* solutionPtr = new FootballBettingGameSolution(solutionMapPtr);
    
    return solutionPtr;
}
