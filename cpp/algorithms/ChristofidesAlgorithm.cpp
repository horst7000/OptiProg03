#include "ChristofidesAlgorithm.h"
#include <lemon/list_graph.h>
#include <lemon/matching.h>
#include <bits/stdc++.h> // fuer INT_MAX
#include <vector>

using namespace lemon;

ChristofidesAlgorithm::ChristofidesAlgorithm() {}

int prim(ListGraph &g, ListGraph::EdgeMap<int> &weight, ListGraph::EdgeMap<bool> &spanningTree) {
    // initialisiere X
    ListGraph::NodeMap<bool>  isNodeInX(g, false);
    isNodeInX[g.nodeFromId(0)] = true;

    int nodeCountX  = 1;
    int totalWeight = 0;

    while(nodeCountX < countNodes(g)) {
        ListGraph::Edge minWeightEdge;
        int minCost = INT_MAX;

        // finde guenstigste Kante (u,v) mit u in X und v nicht in X
        // oder v in X und u nicht in X
        for(ListGraph::EdgeIt a(g); a!=INVALID; ++a) {
            if(
                weight[a] < minCost &&
                ( isNodeInX[g.u(a)] && !isNodeInX[g.v(a)] ||
                isNodeInX[g.v(a)] && !isNodeInX[g.u(a)] )
            ) {
                minWeightEdge = a;
                minCost = weight[minWeightEdge];
            }
        }

        spanningTree[minWeightEdge] = true;
        totalWeight += weight[minWeightEdge];
        
        // fuege v bzw. u zu X hinzu
        if(isNodeInX[g.u(minWeightEdge)])
            isNodeInX[g.v(minWeightEdge)] = true;
        else
            isNodeInX[g.u(minWeightEdge)] = true;
        nodeCountX++;
    }

    return totalWeight;
}


int* bellmanford(ListGraph &g, ListGraph::EdgeMap<int> &weight, int startId, int* prev) {
    // initialization distances
    int* d = new int[countNodes(g)+1];
    std::fill_n(d,countNodes(g)+1,INT_MAX/2);
    d[startId] = 0;

    for (size_t i = 0; i < countNodes(g); i++) // repeat n-1 times
    {
        for(ListGraph::EdgeIt a(g); a!=INVALID; ++a) {
            if(d[g.id(g.u(a))] + weight[a] < d[g.id(g.v(a))]) {
                d[g.id(g.v(a))]    = d[g.id(g.u(a))] + weight[a];
                prev[g.id(g.v(a))] = g.id(g.u(a));
            } else if(d[g.id(g.v(a))] + weight[a] < d[g.id(g.u(a))]) {
                d[g.id(g.u(a))]    = d[g.id(g.v(a))] + weight[a];
                prev[g.id(g.u(a))] = g.id(g.v(a));
            }
        }
    }
    
    // check for negative cycle
    for(ListGraph::EdgeIt a(g); a!=INVALID; ++a) {
        if(d[g.id(g.u(a))] + weight[a] < d[g.id(g.v(a))]) {
            d[g.id(g.v(a))]    = d[g.id(g.u(a))] + weight[a];
            std::cout << "negative cycle exists (ids:) " << g.id(g.u(a)) << " -> " << g.id(g.v(a)) << std::endl;
            std::fill_n(d,countNodes(g),INT_MAX/2);
            return d;
        }
    }
    return d; // array of distance to ids
}

bool ChristofidesAlgorithm::expandGraph(ListGraph &g, ListGraph::EdgeMap<int> &weight) {
    const int countnodes = countNodes(g);
    std::vector<int*> dists(countnodes);
    int* prev = new int[countnodes]();
    int isOneError = -1;
    certGraph.graphPtr = new ListGraph();
    certGraph.labelPtr = new ListGraph::NodeMap<int>(*certGraph.graphPtr);

    for(ListGraph::NodeIt u(g); u!=INVALID; ++u) {
        dists[g.id(u)] = bellmanford(g, weight, g.id(u), prev);
        for (size_t i = 0; i < countnodes; i++)  {

            if(dists[g.id(u)][i] > INT_MAX/3) {  // no path found
                isOneError = g.id(u);
                break;
            }
        }
        if(isOneError != -1)
            break;
    }
    
    if(isOneError != -1) {
        for (size_t i = 0; i < countnodes; i++) {
            if(dists[isOneError][i] < INT_MAX/3) {  // no path found
                auto u = certGraph.graphPtr->addNode();
                (*certGraph.labelPtr)[u] = i+1;
            }
        }
        return false;
    }
    

    for(ListGraph::NodeIt u(g); u!=INVALID; ++u) {
        for(ListGraph::NodeIt v(g); v!=INVALID; ++v) {
            if(u != v && findEdge(g,u,v) == INVALID){
                auto e = g.addEdge(u,v);
                weight[e] = dists[g.id(u)][g.id(v)];
                if(dists[g.id(u)][g.id(v)] == 0)
                std::cout << g.id(u) << " " << g.id(v) << std::endl;
            }
        }
    }
    return true;
}

labeledGraph ChristofidesAlgorithm::getTour(lemon::ListGraph& graph, ListGraph::EdgeMap<int> &weight) {
    tspGraph.graphPtr = new ListGraph();
    tspGraph.weightPtr = new ListGraph::EdgeMap<int>(*tspGraph.graphPtr);
    tspGraph.labelPtr = new ListGraph::NodeMap<int>(*tspGraph.graphPtr);

    auto & tspG      = *tspGraph.graphPtr;
    auto & tspWeight = *tspGraph.weightPtr;
    auto & tspLabel  = *tspGraph.labelPtr;
    
    
    // expand graph
    bool isOneComponent = expandGraph(graph, weight);
    if(!isOneComponent)
        return tspGraph;

    // minimum spanning tree
    ListGraph::EdgeMap<bool> spanningTree(graph);
    ListGraph::NodeMap<int> degree(graph);
    prim(graph, weight, spanningTree);

    // set of nodes with odd degree
    lemon::ListGraph subgraph;
    ListGraph::EdgeMap<int> subweight(subgraph);

    // get degrees
    for(ListGraph::EdgeIt a(graph); a!=INVALID; ++a) {
        if(spanningTree[a]) {
			degree[graph.u(a)]++;
			degree[graph.v(a)]++;
        }
    }

    // copy graph
    for(ListGraph::NodeIt v(graph); v!=INVALID; ++v) {
        subgraph.addNode();
    }
    for(ListGraph::EdgeIt a(graph); a!=INVALID; ++a) {
        ListGraph::Node uOrig = graph.u(a); 
        ListGraph::Node vOrig = graph.v(a); 
        ListGraph::Node uCopy = subgraph.nodeFromId(graph.id(uOrig));
        ListGraph::Node vCopy = subgraph.nodeFromId(graph.id(vOrig)); 
        auto w = subgraph.addEdge(uCopy, vCopy);
        subweight[w] = -weight[a];
    }


    // delete even degree nodes
    for(ListGraph::NodeIt v(graph); v!=INVALID; ++v) {
        if(degree[v] % 2 == 0)
            subgraph.erase(subgraph.nodeFromId(graph.id(v)));
    }
    

    // perfect minmum matching on induced subgraph
    // minWeightPerfectMatching
    MaxWeightedPerfectMatching<ListGraph, ListGraph::EdgeMap<int>> mwpm(subgraph,subweight);
    mwpm.run();

    // combine spanning tree with matching
    for(ListGraph::EdgeIt a(subgraph); a!=INVALID; ++a) {
        if(mwpm.matching(a)) {
            int uMatchId = subgraph.id(subgraph.u(a));
            int vMatchId = subgraph.id(subgraph.v(a));
            auto e = findEdge(graph, graph.nodeFromId(uMatchId), graph.nodeFromId(vMatchId));
            // duplicate existing edges
            if(spanningTree[e] == true) {
                int w = weight[e];
                e = graph.addEdge(graph.nodeFromId(uMatchId), graph.nodeFromId(vMatchId));
                weight[e] = w;
            }
            spanningTree[e] = true;
        }
    }


    // euler tour
    ListGraph::NodeMap<bool> inPath(tspG);
    std::vector<ListGraph::Edge> incompletePath;
    for(ListGraph::NodeIt v(graph); v!=INVALID; ++v) {
        tspG.addNode();
    }
    for(ListGraph::EdgeIt a(graph); a!=INVALID; ++a) {
        ListGraph::Node uOrig = graph.u(a); 
        ListGraph::Node vOrig = graph.v(a); 
        ListGraph::Node uCopy = tspG.nodeFromId(graph.id(uOrig));
        ListGraph::Node vCopy = tspG.nodeFromId(graph.id(vOrig)); 
        tspLabel[uCopy] = graph.id(uOrig)+1;
        tspLabel[vCopy] = graph.id(vOrig)+1;
        auto w = tspG.addEdge(uCopy, vCopy);
        tspWeight[w] = weight[a];
    }
    for(ListGraph::EdgeIt a(graph); a!=INVALID; ++a) {
        if(!spanningTree[a]) {
            int uMatchId = graph.id(graph.u(a));
            int vMatchId = graph.id(graph.v(a));
            auto e = findEdge(tspG, graph.nodeFromId(uMatchId), graph.nodeFromId(vMatchId));
            if(e != INVALID)
                tspG.erase(e);  
        }
    }
    
    for(EulerIt<ListGraph> e(tspG); e!=INVALID; ++e) {
        auto u = tspG.u(e);
        auto v = tspG.v(e);
        incompletePath.push_back(e);
        inPath[u] = true;
        inPath[v] = true;
    }
    std::cout << std::endl << std::endl;
    ListGraph::Node firstU = tspG.u(incompletePath.front());
    ListGraph::Node firstV = tspG.v(incompletePath.front());
    ListGraph::Node lastU  = tspG.u(incompletePath.back());
    ListGraph::Node lastV  = tspG.v(incompletePath.back());
    ListGraph::Node first = (firstU == lastU || firstU == lastV) ? firstU : firstV;
   
    
    std::set<ListGraph::Edge> path;
    ListGraph::NodeMap<bool>  inHamiltonPath(tspG);
    auto previous           = first;
    inHamiltonPath[first]   = true;

    for(auto const& e : incompletePath) {
        auto u = tspG.u(e);
        auto v = tspG.v(e);
        if(u != previous && !inHamiltonPath[u]) {
            auto found = findEdge(tspG,previous,u);
            if(found == INVALID) {
                found            = tspG.addEdge(previous, v);
                auto foundOrig   = findEdge(graph,graph.nodeFromId(tspG.id(previous)),graph.nodeFromId(tspG.id(u)));
                tspWeight[found] = weight[foundOrig];
            }
            path.insert(found);
            previous = u;
            inHamiltonPath[u] = true;
        } else if(v != previous && !inHamiltonPath[v]) {
            auto found = findEdge(tspG,previous,v);
            if(found == INVALID) {
                found            = tspG.addEdge(previous, v);
                auto foundOrig   = findEdge(graph,graph.nodeFromId(tspG.id(previous)),graph.nodeFromId(tspG.id(v)));
                tspWeight[found] = weight[foundOrig];
            }
            path.insert(found);
            previous = v;
            inHamiltonPath[v] = true;
        }
    }
    path.insert(findEdge(tspG,previous,first));

    // create hamilton circle
    for(ListGraph::EdgeIt a(tspG); a!=INVALID; ++a) {
        if(path.find(a) == path.end()) {
            tspG.erase(a);
        }
    }
    return tspGraph; // return the tour here
}

/**
 * Returns a certificate is there is no TSP tour in {@code graph}
 *
 * @param graph h the graph to calculate a TSP Tour for
 * @return a certificate
 */
labeledGraph ChristofidesAlgorithm::getNonTSPCertificate(lemon::ListGraph& graph) {
    return certGraph; // return certificate here
}
