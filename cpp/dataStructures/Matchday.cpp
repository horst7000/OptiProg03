#include "Matchday.h"

Matchday::Matchday(int number, std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>> &matches) {
    this->number = number;
    this->matches = matches;
}

Matchday::~Matchday() {}

int Matchday::getNumber() const {
    return number;
}

const std::map<std::pair<FootballTeam, FootballTeam>, std::pair<int, int>> &Matchday::getMatches() const {
    return matches;
}

std::ostream &operator<<(std::ostream &os, const Matchday &matchday) {
    os << "number: " << matchday.number << " matches: ";
    os << "{";
    for(auto &pair : matchday.matches) {
        os << "((" << pair.first.first << ", " << pair.first.second << ") -> (" << pair.second.first << ", " <<  pair.second.second << "))";
        os << "  ";
    }
    os << "}";
    return os;
}
