#ifndef A2_SIMPLE_NAVIGATOR_V1_0_CLI_HPP_
#define A2_SIMPLE_NAVIGATOR_V1_0_CLI_HPP_

#include <iostream>
#include <string>

#include "../graph/s21_graph.hpp"
#include "../graph_algorithms/s21_graph_algorithms.hpp"

namespace s21 {

class CommandLineInterface {
 public:
  CommandLineInterface();
  void run();

 private:
  void chooseAction();
  void loadGraphFromFile();
  void printDepthFirstSearch();
  void printBreadthFirstSearch();
  void printShortestPathBetweenVertices();
  void printShortestPathsBetweenAllVertices();
  void printLeastSpanningTree();
  void printSolveTravelingSalesmanProblem();
  void exportToDotFIle();

  s21::Graph graph;
  s21::GraphAlgorithms algorithms;
};
}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_V1_0_CLI_HPP_
