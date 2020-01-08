#ifndef CPP_BIPARTITEMATCHINGALGORITHM_H
#define CPP_BIPARTITEMATCHINGALGORITHM_H

#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/matching.h>


class BipartiteMatchingAlgorithm {
private:

public:
    /**
     * Constructor for BipartiteMatchingAlgorithm
     */
    BipartiteMatchingAlgorithm();

    /**
     * Calculates a matching for a bipartite graph.
     *
     * @return the maximum matching for the given graph.
     */
    std::map<int, int>* getMatching(lemon::ListGraph& graph, lemon::ListGraph::EdgeMap<int> weight);
};


#endif //CPP_BIPARTITEMATCHINGALGORITHM_H
