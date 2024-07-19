#ifndef A2_SIMPLE_NAVIGATOR_SRC_GRAPH_HPP_
#define A2_SIMPLE_NAVIGATOR_SRC_GRAPH_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../containers/s21_queue.hpp"
#include "../containers/s21_stack.hpp"

namespace s21 {

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_matrix;

 public:
  Graph();

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);
  bool isConnectedGraph();
  bool isSquareMatrix();
  bool isNaturalWeights();
  bool isCorrectMatrix();

  bool isDirectedGraph();
  bool isWeightedGraph();
  std::vector<std::vector<int>> getAdjacencyMatrix();

  void printMatrix();
};

}  // namespace s21

#endif  // A2_SIMPLE_NAVIGATOR_SRC_GRAPH_HPP_