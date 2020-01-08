#ifndef CPP_CHRISTOFIDESALGORITHM_H
#define CPP_CHRISTOFIDESALGORITHM_H

#include <lemon/concepts/graph.h>
#include <lemon/list_graph.h>
#include <lemon/path.h>

class ChristofidesAlgorithm {
private:

public:

    ChristofidesAlgorithm();

    /**
     * Calculates a TSP tour for the given {@code graph}.
     *
     * @param graph the graph to calculate a TSP Tour for
     * @return a TSP tour
     */
    lemon::ListGraph* getTour(lemon::ListGraph& graph);

    /**
     * Returns a certificate is there is no TSP tour in {@code graph}
     *
     * @param graph h the graph to calculate a TSP Tour for
     * @return a certificate
     */
    lemon::ListGraph* getNonTSPCertificate(lemon::ListGraph& graph);

};

#endif //CPP_CHRISTOFIDESALGORITHM_H
