#ifndef S21_GRAPH_ALGORITHMS
#define S21_GRAPH_ALGORITHMS

#include <algorithm>
#include <exception>
#include <limits>
#include <random>
#include <vector>

#include "../containers/s21_queue.hpp"
#include "../containers/s21_stack.hpp"
#include "../graph/s21_graph.hpp"

namespace s21 {

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);
};

class AntAlgorithm {
 public:
  AntAlgorithm(Graph &graph);
  TsmResult getMinPath();

 private:
  Graph &graph;
  const double Alpha = 1.0;
  const double Beta = 2.0;
  const double Pheromone = 1.0;
  const double Q = 1.0;
  const double Evaporation = 0.3;

  double getRandom();
  TsmResult getWayOfAnt(std::vector<std::vector<double>> &tau, int index);
  std::vector<int> getFreeVertices(std::vector<bool> &vertices, int index);
  std::vector<double> getProbability(std::vector<int> &freeVertices,
                                     std::vector<std::vector<double>> &tau,
                                     int index);
  int getNextVertex(std::vector<int> &freeVertices,
                    std::vector<double> &probabilityVector);
  void updatePheromone(std::vector<std::vector<double>> &tau,
                       std::vector<TsmResult> &waysAnts);
  void normalizeResult(std::vector<int> &result);
};

}  // namespace s21

#endif  // S21_GRAPH_ALGORITHMS
