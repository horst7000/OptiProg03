#ifndef CPP_FOOTBALLTEAM_H
#define CPP_FOOTBALLTEAM_H


#include <string>
#include <ostream>

class FootballTeam {

private:
    /**
     * the name of the football team
     */
    std::string name;

public:
    /**
     * Constructor for FootballTeam
     *
     * @param name the name of the football team
     */
    FootballTeam(std::string &name);

    /**
     * Destructor for FootballTeam
     */
    ~FootballTeam();

    /**
     * Getter for name.
     *
     * @return the name
     */
    const std::string &getName() const;

    friend std::ostream &operator<<(std::ostream &os, const FootballTeam &team);

    bool operator<(const FootballTeam &rhs) const;

    bool operator>(const FootballTeam &rhs) const;

    bool operator<=(const FootballTeam &rhs) const;

    bool operator>=(const FootballTeam &rhs) const;
};


#endif //CPP_FOOTBALLTEAM_H
