#include <lemon/concepts/graph.h>
#include "BipartitionAlgorithm.h"


BipartitionAlgorithm::BipartitionAlgorithm() {}

// red : if node should be colored red
void BipartitionAlgorithm::recursivePartitioning(ListGraph::Node node, ListBpGraph::Node predecessor, bool red) {
    auto & biGraph  = *labGraph.graphPtr;
    auto & biLabel  = *labGraph.labelPtr;
    auto & graph    = *graphPtr;

    int nodeLabel = graph.id(node)+1;    

    // look for  node  in already colored nodes (in bipartit graph)
    if((*isColored)[node]) {
        for(ListBpGraph::NodeIt u(biGraph); u!=INVALID; ++u) {
            if(biLabel[u] == nodeLabel) { // node found  as "u"
                if(labGraph.graphPtr->blue(u) == red) { // invalid colorization
                    colorError     = nodeLabel;
                    pre[nodeLabel] = biLabel[predecessor];
                } else {
                    addEdge(u, predecessor, red);
                }
                return;
            }
        }
    }

    // new vertex
    ListBpGraph::Node v;
    if(red)
        v = labGraph.graphPtr->addRedNode();
    else
        v = labGraph.graphPtr->addBlueNode();
    biLabel[v]      = nodeLabel; // sync label of new graph with original graph
    pre[nodeLabel]  = (predecessor == INVALID) ? -1 : biLabel[predecessor]; // save predecessor if valid

    // new edge
    addEdge(v, predecessor, red);


    (*isColored)[node] = true;    // mark node as colored

    for(ListGraph::EdgeIt e(graph); e!=INVALID; ++e) {
        ListGraph::Node w = graph.oppositeNode(node,e);
        if(w != INVALID && colorError == -1)
            recursivePartitioning(w, v, !red);
    }

}

ListBpGraph::Edge BipartitionAlgorithm::addEdge(ListBpGraph::Node v, ListBpGraph::Node predecessor, bool isVRed) {
    auto & biGraph  = *labGraph.graphPtr;
    auto & biLabel  = *labGraph.labelPtr;
    auto & biWeight = *labGraph.weightPtr;
    auto & graph    = *graphPtr;
    auto & weight   = *weightPtr;
    ListBpGraph::Edge e = findEdge(biGraph,v,predecessor);

    if(e == INVALID && predecessor != INVALID) {
        if(isVRed) // => predecessor is blue
            e = biGraph.addEdge(biGraph.asBlueNode(predecessor), biGraph.asRedNode(v));
        else
            e = biGraph.addEdge(biGraph.asBlueNode(v), biGraph.asRedNode(predecessor));

        // add edge to weight
        auto vOrig   = graph.nodeFromId(biLabel[v]-1);
        auto preOrig = graph.nodeFromId(biLabel[predecessor]-1);
        int eWeight = weight[findEdge(graph, vOrig, preOrig)];
        biWeight[e] = eWeight;
    }

    return e;
}

labeledBiGraph BipartitionAlgorithm::getPartitioning(lemon::ListGraph& graph,  ListGraph::EdgeMap<int>& weight) {
    // initialization
    pre = new int[countNodes(graph)+1]; // array to save the predecessor label
    std::fill_n(pre,countNodes(graph)+1,-1);
    colorError = -1;
    isColored = new ListGraph::NodeMap<bool>(graph);

    labGraph.graphPtr = new ListBpGraph();
    labGraph.labelPtr = new ListBpGraph::NodeMap<int>(*labGraph.graphPtr);
    labGraph.weightPtr = new ListBpGraph::EdgeMap<int>(*labGraph.graphPtr);

    graphPtr = &graph;
    weightPtr = &weight;

    // algorithm
    for(ListGraph::NodeIt n(graph); n!=INVALID; ++n) {
		if(!(*isColored)[n] && colorError == -1)
            recursivePartitioning(n, INVALID, true);
    }


    this->nonBipartitionCertificate = new NonBipartitionCertificate(pre, colorError);

    return labGraph; // TODO return bipartition here or empty partition if there is non
}

NonBipartitionCertificate* BipartitionAlgorithm::getNonBipartitionCertificate(lemon::ListGraph& graph, ListGraph::EdgeMap<int>& weight) {
    if(nonBipartitionCertificate == nullptr) {
        getPartitioning(graph, weight);
    }
    return nonBipartitionCertificate;
}

bool BipartitionAlgorithm::isValidPartitioning(lemon::ListBpGraph& partitioning) {

    // TODO implement verification algorithm for bipartitions
    // ???
    // lemon::ListBpGraph is always bipartit

    return (colorError == -1); // -1 is valid state
}
