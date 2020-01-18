#include <lemon/concepts/graph.h>
#include "BipartiteMatchingAlgorithm.h"
#include <bits/stdc++.h> // fuer INT_MAX

using namespace lemon;

int* bellmanford(ListDigraph &g, ListDigraph::ArcMap<int> &weight, int startId, int* prev) {
    // initialization distances
    int* d = new int[countNodes(g)+1];
    std::fill_n(d,countNodes(g)+1,INT_MAX/2);
    d[startId] = 0;

    for (size_t i = 0; i < countNodes(g); i++) // repeat n-1 times
    {
        for(ListDigraph::ArcIt a(g); a!=INVALID; ++a) {
            if(d[g.id(g.source(a))] + weight[a] < d[g.id(g.target(a))]) {
                d[g.id(g.target(a))]    = d[g.id(g.source(a))] + weight[a];
                prev[g.id(g.target(a))] = g.id(g.source(a));
            }
        }
    }
    
    // check for negative cycle
    for(ListDigraph::ArcIt a(g); a!=INVALID; ++a) {
        if(d[g.id(g.source(a))] + weight[a] < d[g.id(g.target(a))]) {
            d[g.id(g.target(a))]    = d[g.id(g.source(a))] + weight[a];
            std::cout << "negative cycle exists (ids:) " << g.id(g.source(a)) << " -> " << g.id(g.target(a)) << std::endl;
            std::fill_n(d,countNodes(g),INT_MAX/2);
            return d;
        }
    }
    return d; // array of distance to ids
}

BipartiteMatchingAlgorithm::BipartiteMatchingAlgorithm() {}

/**
 *                    B
 *          R         l
 *   s ->   e    X    u  ->   t
 *          d         e   
 */
void BipartiteMatchingAlgorithm::fillDigraphFromBipartiteAndMatching() {
    // initialization
    diGraphPtr  = new ListDigraph();
    labelPtr    = new ListDigraph::NodeMap<int>(*diGraphPtr);
    weightPtr   = new ListDigraph::ArcMap<int>(*diGraphPtr, 0);
    auto & diGraph  = *diGraphPtr;
    auto & label    = *labelPtr;
    auto & weight   = *weightPtr;
    ListDigraph::NodeMap<bool> isInMatching(*diGraphPtr);

    auto & biGraph  = *partitioning.graphPtr;
    auto & biLabel  = *partitioning.labelPtr;
    auto & biWeight = *partitioning.weightPtr;

    auto & matching = *matchingPtr;
    

    // copy nodes
    for(ListBpGraph::NodeIt u(biGraph); u!=INVALID; ++u) {
			diGraph.addNode();
	}
    // copy edges as arcs with respect to existing matching
    for(ListBpGraph::EdgeIt e(biGraph); e!=INVALID; ++e) {
            ListBpGraph::Node nRed  = biGraph.redNode(e);
            ListBpGraph::Node nBlue = biGraph.blueNode(e);
			int redId  = biGraph.id(nRed);
			int blueId = biGraph.id(nBlue);
            ListDigraph::Node diRed = diGraph.nodeFromId(redId);
            ListDigraph::Node diBlue = diGraph.nodeFromId(blueId);
            label[diRed]  = biLabel[nRed];
            label[diBlue] = biLabel[nBlue];

            ListDigraph::Arc a;
            if(matching[e]) {
                a = diGraph.addArc( diBlue, diRed );
                weight[a] = biWeight[e];
                isInMatching[diBlue] = true;
                isInMatching[diRed] = true;
            } else {
                a = diGraph.addArc( diRed, diBlue );
                weight[a] = -biWeight[e];
            }
	}
    // connect nodes outside of matching with extra nodes s,t
    s = diGraph.addNode();
    t = diGraph.addNode();
    for(ListDigraph::NodeIt u(diGraph); u!=INVALID; ++u) {
        int id = diGraph.id(u);
        
        if(u == s || u == t)
            continue;
        
        if(!isInMatching[u]) {
            if(biGraph.red(biGraph.nodeFromId(id)))
                diGraph.addArc(s,u);
            else
                diGraph.addArc(u,t);
        }
	}

    // std::cout << countNodes(diGraph) << std::endl;
    // std::cout << countArcs(diGraph) << std::endl;
}

void BipartiteMatchingAlgorithm::augmentMatching(ListBpGraph::EdgeMap<bool>& augmentingPath) {
    for(ListBpGraph::EdgeIt e(*partitioning.graphPtr); e!=INVALID; ++e) {
        (*matchingPtr)[e] = (*matchingPtr)[e] ^ augmentingPath[e]; // ^ is XOR
    }
}

std::map<int, int>* BipartiteMatchingAlgorithm::getMatching(lemon::ListGraph& graph, lemon::ListGraph::EdgeMap<int>& weight) {
    // initialization
    mapPtr      = new std::map<int, int>();

    // check graph properties
    auto* bipartitionAlgorithm = new BipartitionAlgorithm();
    partitioning = bipartitionAlgorithm->getPartitioning(graph, weight);
    if(!bipartitionAlgorithm->getNonBipartitionCertificate(graph, weight)->isValidPartitioning())
        return mapPtr;
    
    // dereferencing
    auto & biGraph  = *partitioning.graphPtr;
    auto & biLabel  = *partitioning.labelPtr;

    // initialization matching
    matchingPtr = new ListBpGraph::EdgeMap<bool>(biGraph);
    auto & matching = *matchingPtr;

    for (size_t i = 0; i < countEdges(biGraph); i++)
    {
        // bipartite -> digraph
        fillDigraphFromBipartiteAndMatching();
        auto & label    = *labelPtr;

        // run Bellman-Ford
        int* prev = new int[diGraphPtr->maxNodeId()+1];
        std::fill_n(prev, diGraphPtr->maxNodeId()+1, diGraphPtr->id(s));
        int* dist = bellmanford(*diGraphPtr, *weightPtr, diGraphPtr->id(s), prev);

        if(dist[diGraphPtr->id(t)] > INT_MAX/3) // no path  s -> t  found
            break;

        // fill path as shortest path (Bellman-Ford) from s -> t 
        ListBpGraph::EdgeMap<bool> augmentingPath(biGraph);
        int prevId = diGraphPtr->id(t);
        prevId = prev[prevId];
        while (prevId != diGraphPtr->id(s))
        {
            ListBpGraph::Edge e = findEdge(biGraph, biGraph.nodeFromId(prevId), biGraph.nodeFromId(prev[prevId]));
            if(e != INVALID)
                augmentingPath[e] = true;
            prevId = prev[prevId];
        }
        
        augmentMatching(augmentingPath);

        // for(ListBpGraph::EdgeIt e(*partitioning.graphPtr); e!=INVALID; ++e) {
        //     if(matching[e])
        //         std::cout << biLabel[biGraph.redNode(e)] << " -> " << biLabel[biGraph.blueNode(e)]  << std::endl;
        // }
        // std::cout << std::endl;
    }
    for(ListBpGraph::EdgeIt e(*partitioning.graphPtr); e!=INVALID; ++e) {
        if(matching[e])
            (*mapPtr)[biLabel[biGraph.redNode(e)]] = biLabel[biGraph.blueNode(e)];
    }

    return mapPtr; // TODO return Matching here
}
