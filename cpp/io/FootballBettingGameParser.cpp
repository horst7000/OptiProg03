#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "FootballBettingGameParser.h"

std::list<Matchday>* FootballBettingGameParser::parseInstance(std::string &path) {
    auto* list = new std::list<Matchday>();

    std::ifstream stream(path);

    int number = 0;
    std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>> matches = (*new std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>>());
    Matchday* currentMatchday = nullptr;

    if(stream.is_open()) {
        std::string line;
        while (std::getline(stream,line)) {

            if (!line.empty()) {
                if (line.at(0) == '#') {
                    if(number > 0) {
                        currentMatchday = new Matchday(number, matches);
                        list->insert(list->end(), (*currentMatchday));
                    }
                    number++;
                    matches = (*new std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>>());
                } else {
                    auto* items = new std::vector<std::string>;
                    // split line at ','
                    size_t pos = 0;
                    std::string token;
                    while ((pos = line.find(',')) != std::string::npos) {
                        token = line.substr(0, pos);
                        items->insert(items->end(), token);
                        line.erase(0, pos + 1);
                    }
                    token = line.substr(0, pos);
                    items->insert(items->end(), token);

                    auto* pairing = new std::pair<FootballTeam, FootballTeam>((*new FootballTeam(items->at(0))),(*new FootballTeam(items->at(1))));
                    auto* result = new std::pair<int, int>(std::stoi(items->at(2)), std::stoi(items->at(3)));
                    auto* toInsert = new std::pair<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>>((*pairing), (*result));
                    matches.insert((*toInsert));
                }
            }
        }
        if(number > 0) {
            currentMatchday = new Matchday(number, matches);
            list->insert(list->end(), (*currentMatchday));
        }
    } else {
        std::cout << "Unable to open file!";
    }

    return list;
}
