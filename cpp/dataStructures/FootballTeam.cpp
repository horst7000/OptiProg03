#include "FootballTeam.h"

FootballTeam::FootballTeam(std::string &name) {
    this->name = name;
}

FootballTeam::~FootballTeam() {}

std::ostream &operator<<(std::ostream &os, const FootballTeam &team) {
    os << "name: " << team.name;
    return os;
}

const std::string &FootballTeam::getName() const {
    return name;
}

bool FootballTeam::operator<(const FootballTeam &rhs) const {
    return name < rhs.name;
}

bool FootballTeam::operator>(const FootballTeam &rhs) const {
    return rhs < *this;
}

bool FootballTeam::operator<=(const FootballTeam &rhs) const {
    return !(rhs < *this);
}

bool FootballTeam::operator>=(const FootballTeam &rhs) const {
    return !(*this < rhs);
}
