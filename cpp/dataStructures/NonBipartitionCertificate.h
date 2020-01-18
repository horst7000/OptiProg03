#ifndef CPP_NONBIPARTITIONCERTIFICATE_H
#define CPP_NONBIPARTITIONCERTIFICATE_H


#include <lemon/list_graph.h>
#include <ostream>

class NonBipartitionCertificate {
private:
    int* pre;
    int begin;
public:
    NonBipartitionCertificate(int* pre, int begin) : pre(pre), begin(begin) {}
    bool isValidPartitioning() { return begin == -1; }

    friend std::ostream &operator<<(std::ostream &os, const NonBipartitionCertificate &certificate);
};


#endif //CPP_NONBIPARTITIONCERTIFICATE_H
