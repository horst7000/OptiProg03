#ifndef CPP_BIPARTITIONALGORITHM_H
#define CPP_BIPARTITIONALGORITHM_H

#include <lemon/list_graph.h>
#include "../dataStructures/NonBipartitionCertificate.h"

class BipartitionAlgorithm {
private:
    NonBipartitionCertificate* nonBipartitionCertificate;

public:

    BipartitionAlgorithm();

    /**
     * Calculates a bipartition of the graph.
     *
     * @return a bipartition of graph or empty partition if there is no bipartition
     */
    lemon::ListBpGraph* getPartitioning(lemon::ListGraph& graph);

    /**
     * Returns the non-bipartition certificate if graph is not bipartite, null otherwise.
     * If getPartitioning was not called before, getPartitioning is called.
     *
     * @return the non-bipartition certificate, null otherwise
     */
    NonBipartitionCertificate* getNonBipartitionCertificate(lemon::ListGraph& graph);

    /**
     * Checks whether {@code partitioning} is a valid bipartite partitioning.
     *
     * @param partitioning the partitioning to check
     * @return true if partitioning is valid bipartite partitioning for {@code graph}, false otherwise
     */
    bool isValidPartitioning(lemon::ListBpGraph& partitioning);
};

#endif //CPP_BIPARTITIONALGORITHM_H
