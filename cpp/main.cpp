#include <iostream>
#include <lemon/lgf_reader.h>
#include <lemon/concepts/graph.h>
#include "algorithms/BipartiteMatchingAlgorithm.h"
#include "algorithms/BipartitionAlgorithm.h"
#include "algorithms/ChristofidesAlgorithm.h"
#include "io/FootballBettingGameParser.h"
#include "algorithms/FootballBettingGameAlgorithm.h"

/**
     *
     *
     * @param args args[0] is the number of the exercise (decides the algorithm which is to be executed)
     *             args[1] is the file to parse
     */
int main(int argc, char **argv) {

    if(argc < 3) {
        std::cout << argc << std::endl;
        for (int i = 0; i < argc; ++i) {
            std::cout << i << ": " << argv[i] << std::endl;
        }
        return -1;
    }

    std::string arg0(argv[1]);
    std::string arg1(argv[2]);

    

    if(arg0 == "2") { // exercise 2
        std::cout << "Executing BipartititeMatchingAlgorithm" << std::endl;

        auto* graph = new lemon::ListGraph();
        auto* reader = new lemon::GraphReader<lemon::ListGraph>(*graph, arg1);
        lemon::ListGraph::NodeMap<int> label(*graph);
        lemon::ListGraph::EdgeMap<int> weight(*graph);
        reader->nodeMap("label", label)
            .edgeMap("weight", weight)
            .run();

        auto* bipartiteMatchingAlgorithm = new BipartiteMatchingAlgorithm();

        std::cout << "{";
        for(auto &pair : *bipartiteMatchingAlgorithm->getMatching(*graph, weight)) {
            std::cout << "(" << pair.first << " -> " << pair.second << ")";
        }
        std::cout << "}";

    } else if(arg0 == "1") { // exercise 1

        std::cout << "Executing BipartitionAlgorithm" << std::endl;

        auto* graph = new lemon::ListGraph();
        auto* reader = new lemon::GraphReader<lemon::ListGraph>(*graph, arg1);
        lemon::ListGraph::NodeMap<int> label(*graph);
        lemon::ListGraph::EdgeMap<int> weight(*graph);
        reader->nodeMap("label", label)
                .edgeMap("weight", weight)
                .run();

        auto* bipartitionAlgorithm = new BipartitionAlgorithm();

        labeledBiGraph partitioning = bipartitionAlgorithm->getPartitioning(*graph, weight);

        (new lemon::BpGraphWriter<lemon::ListBpGraph>(*partitioning.graphPtr, std::cout))
            ->nodeMap("label", *partitioning.labelPtr)
            .edgeMap("weight", *partitioning.weightPtr)
            .run();
        std::cout << std::endl;

        std::cout << "is valid partitioning?   ";
        std::cout << bipartitionAlgorithm->isValidPartitioning(*partitioning.graphPtr) << std::endl;
        std::cout << *bipartitionAlgorithm->getNonBipartitionCertificate(*graph, weight) << std::endl;

    } else if(arg0 == "3") {
        std::cout << "Executing FootballBettingGameAlgorithm" << std::endl;

        auto* footballBettingGameParser = new FootballBettingGameParser();
        std::list<Matchday>* matchdays = footballBettingGameParser->parseInstance(arg1);

        auto* footballBettingGameAlgorithm = new FootballBettingGameAlgorithm();

        FootballBettingGameSolution* footballBettingGameSolution = footballBettingGameAlgorithm->calculateSolution(*matchdays);

        std::cout << "{";
            for (const auto &pair : *footballBettingGameSolution->getSolution()) {
                std::cout << "(" << pair.first << "   ->    " << *pair.second << ")" << std::endl << std::endl;
            }
        std::cout << "}";

    } else if(arg0 == "4") {
        std::cout << "Executing ChristofidesAlgorithm" << std::endl;

        auto* graph = new lemon::ListGraph();
        auto* reader = new lemon::GraphReader<lemon::ListGraph>(*graph, arg1);
        lemon::ListGraph::NodeMap<int> label(*graph);
        lemon::ListGraph::EdgeMap<int> weight(*graph);
        reader->nodeMap("label", label)
                .edgeMap("weight", weight)
                .run();

        auto* tspAlgorithm = new ChristofidesAlgorithm();
        labeledGraph touri = tspAlgorithm->getTour(*graph, weight);
        (new lemon::GraphWriter<lemon::ListGraph>(*touri.graphPtr, std::cout))
            ->nodeMap("label", *touri.labelPtr)
            .edgeMap("weight", *touri.weightPtr)
            .run();
        std::cout << std::endl;

        // (new lemon::GraphWriter<lemon::ListGraph>(*tspAlgorithm->getNonTSPCertificate(*graph), std::cout))->run();
        labeledGraph cert = tspAlgorithm->getNonTSPCertificate(*graph);
        (new lemon::GraphWriter<lemon::ListGraph>(*cert.graphPtr, std::cout))
            ->nodeMap("label", *cert.labelPtr)
            .run();
        std::cout << std::endl;
    }
}
