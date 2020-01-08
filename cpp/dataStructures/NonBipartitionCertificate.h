#ifndef CPP_NONBIPARTITIONCERTIFICATE_H
#define CPP_NONBIPARTITIONCERTIFICATE_H


#include <lemon/list_graph.h>
#include <ostream>

class NonBipartitionCertificate {
    // TODO implement your data structure for a non-bipartition certificate here
private:

public:
    /**
     * Returns the certificate
     *
     * @return the certificate
     */
    lemon::ListGraph* getCertificate();

    friend std::ostream &operator<<(std::ostream &os, const NonBipartitionCertificate &certificate);
};


#endif //CPP_NONBIPARTITIONCERTIFICATE_H
