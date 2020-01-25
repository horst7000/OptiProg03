#ifndef CPP_CHRISTOFIDESALGORITHM_H
#define CPP_CHRISTOFIDESALGORITHM_H

#include <lemon/concepts/graph.h>
#include <lemon/euler.h>
#include <lemon/list_graph.h>
#include <lemon/path.h>





struct labeledGraph {
    lemon::ListGraph* graphPtr;
    lemon::ListGraph::NodeMap<int>* labelPtr;
    lemon::ListGraph::EdgeMap<int>* weightPtr;
};

class ChristofidesAlgorithm {
private:
    labeledGraph tspGraph;
    labeledGraph certGraph;

    bool expandGraph(lemon::ListGraph &g, lemon::ListGraph::EdgeMap<int> &weight);

public:

    ChristofidesAlgorithm();

    /**
     * Calculates a TSP tour for the given {@code graph}.
     *
     * @param graph the graph to calculate a TSP Tour for
     * @return a TSP tour
     */
    labeledGraph getTour(lemon::ListGraph& graph, lemon::ListGraph::EdgeMap<int> &weight);

    /**
     * Returns a certificate is there is no TSP tour in {@code graph}
     *
     * @param graph h the graph to calculate a TSP Tour for
     * @return a certificate
     */
    labeledGraph getNonTSPCertificate(lemon::ListGraph& graph);

};

#endif //CPP_CHRISTOFIDESALGORITHM_H
