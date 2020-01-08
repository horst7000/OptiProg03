#ifndef CPP_MATCHDAY_H
#define CPP_MATCHDAY_H

#include <ostream>
#include <map>
#include "FootballTeam.h"

class Matchday {

private:
    int number;
    std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>> matches;

public:
    Matchday(int number, std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>> &matches);

    ~Matchday();

    int getNumber() const;

    const std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>>& getMatches() const;

    friend std::ostream& operator<<(std::ostream &os, const Matchday &matchday);
};


#endif //CPP_MATCHDAY_H
