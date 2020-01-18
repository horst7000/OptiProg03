#ifndef CPP_BIPARTITIONALGORITHM_H
#define CPP_BIPARTITIONALGORITHM_H

#include <lemon/list_graph.h>
#include "../dataStructures/NonBipartitionCertificate.h"

using namespace lemon;

struct labeledBiGraph {
    lemon::ListBpGraph* graphPtr;
    lemon::ListBpGraph::NodeMap<int>* labelPtr;
    lemon::ListBpGraph::EdgeMap<int>* weightPtr;
};

class BipartitionAlgorithm {
private:
    NonBipartitionCertificate* nonBipartitionCertificate;
    labeledBiGraph labGraph;
    int* pre;
    int colorError;
    lemon::ListGraph::NodeMap<bool>* isColored;

    ListGraph* graphPtr;
    ListGraph::EdgeMap<int>* weightPtr;

    void recursivePartitioning(ListGraph::Node, ListBpGraph::Node, bool red);
    ListBpGraph::Edge addEdge(ListBpGraph::Node v, ListBpGraph::Node predecessor, bool isVRed);

public:

    BipartitionAlgorithm();

    /**
     * Calculates a bipartition of the graph.
     *
     * @return a bipartition of graph or empty partition if there is no bipartition
     */
    labeledBiGraph getPartitioning(lemon::ListGraph& graph,  ListGraph::EdgeMap<int>& weight);

    /**
     * Returns the non-bipartition certificate if graph is not bipartite, null otherwise.
     * If getPartitioning was not called before, getPartitioning is called.
     *
     * @return the non-bipartition certificate, null otherwise
     */
    NonBipartitionCertificate* getNonBipartitionCertificate(lemon::ListGraph& graph, ListGraph::EdgeMap<int>& weight);

    /**
     * Checks whether {@code partitioning} is a valid bipartite partitioning.
     *
     * @param partitioning the partitioning to check
     * @return true if partitioning is valid bipartite partitioning for {@code graph}, false otherwise
     */
    bool isValidPartitioning(lemon::ListBpGraph& partitioning);
};

#endif //CPP_BIPARTITIONALGORITHM_H
