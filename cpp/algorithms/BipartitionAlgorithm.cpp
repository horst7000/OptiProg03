#include <lemon/concepts/graph.h>
#include "BipartitionAlgorithm.h"

BipartitionAlgorithm::BipartitionAlgorithm() {}

lemon::ListBpGraph* BipartitionAlgorithm::getPartitioning(lemon::ListGraph& graph) {
    // TODO check graph properties

    // TODO implement bipartition algorithm here

    // TODO implement calculation of non-bipartition certificate here
    this->nonBipartitionCertificate = new NonBipartitionCertificate();

    return nullptr; // TODO return bipartition here or empty partition if there is non
}

NonBipartitionCertificate* BipartitionAlgorithm::getNonBipartitionCertificate(lemon::ListGraph& graph) {
    if(nonBipartitionCertificate == nullptr) {
        getPartitioning(graph);
    }
    return nonBipartitionCertificate;
}

bool BipartitionAlgorithm::isValidPartitioning(lemon::ListBpGraph& partitioning) {

    // TODO implement verification algorithm for bipartitions

    return false;
}
