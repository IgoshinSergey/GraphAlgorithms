#include "s21_graph_algorithms.hpp"

std::vector<int> s21::GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                        int start_vertex) {
  if (!graph.isCorrectMatrix()) {
    throw std::logic_error("Adjency matrix is not correct");
  }
  std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
  int size = static_cast<int>(adjacencyMatrix.size());
  if (start_vertex > size || start_vertex <= 0)
    throw std::invalid_argument("Invalid start_vertex");
  std::vector<bool> nodes(adjacencyMatrix.size(), false);
  std::vector<int> vertexes;
  s21::stack<int> st;
  st.push(start_vertex - 1);
  while (!st.empty()) {
    int v = st.top();
    st.pop();
    if (nodes[v]) continue;
    nodes[v] = true;
    for (int i = size - 1; i >= 0; i--) {
      if (adjacencyMatrix[v][i] && !nodes[i]) {
        st.push(i);
      }
    }
    vertexes.push_back(v + 1);
  }
  return vertexes;
}
std::vector<int> s21::GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                          int start_vertex) {
  if (!graph.isCorrectMatrix()) {
    throw std::logic_error("Adjency matrix is not correct");
  }
  std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
  int size = static_cast<int>(adjacencyMatrix.size());
  if (start_vertex > size || start_vertex <= 0)
    throw std::invalid_argument("Invalid start_vertex");
  std::vector<bool> nodes(adjacencyMatrix.size(), false);
  std::vector<int> vertexes;
  s21::queue<int> qu;
  qu.push(start_vertex - 1);
  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();
    if (nodes[v]) continue;
    nodes[v] = true;
    for (int i = 0; i < size; i++) {
      if (adjacencyMatrix[v][i] && !nodes[i] && v != i) {
        qu.push(i);
      }
    }
    vertexes.push_back(v + 1);
  }
  return vertexes;
}

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  if (vertex1 <= 0 || vertex2 <= 0)
    throw std::invalid_argument("Vertex number is less than or equal to zero");
  std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
  int size = static_cast<int>(adjacencyMatrix.size());
  if (vertex1 > size || vertex2 > size)
    throw std::invalid_argument(
        "The vertex number is greater than the maximum possible vertex number "
        "in the graph");
  std::vector<bool> vertexes(size, false);
  std::vector<int> lens(size, std::numeric_limits<int>::max());
  std::vector<int> prev(size, -1);
  int v = vertex1 - 1;
  vertexes[v] = true;
  lens[v] = 0;
  bool flag = false;
  while (true) {
    for (int i = 0; i < size; i++) {
      if (!vertexes[i] && adjacencyMatrix[v][i]) {
        if (lens[i] > adjacencyMatrix[v][i] + lens[v]) {
          lens[i] = adjacencyMatrix[v][i] + lens[v];
          prev[i] = v;
        }
      }
    }

    int min_vertex = -1, min_val = std::numeric_limits<int>::max();
    for (int i = 0; i < size; i++) {
      if (!vertexes[i] && lens[i] < min_val) {
        min_val = lens[i];
        min_vertex = i;
      }
    }
    if (min_vertex == -1) {
      break;
    }
    if (min_vertex == vertex2 - 1) {
      flag = true;
      break;
    }
    v = min_vertex;
    vertexes[v] = true;
  }
  if (flag) return lens[vertex2 - 1];
  throw std::logic_error("There is no such thing as a path");
}

std::vector<std::vector<int>>
s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  std::vector<std::vector<int>> shortestPathMatrix = graph.getAdjacencyMatrix();
  int size = static_cast<int>(shortestPathMatrix.size());
  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (i != j && i != k && j != k && shortestPathMatrix[i][k] &&
            shortestPathMatrix[k][j]) {
          if (!shortestPathMatrix[i][j] ||
              shortestPathMatrix[i][j] >
                  shortestPathMatrix[i][k] + shortestPathMatrix[k][j])
            shortestPathMatrix[i][j] =
                shortestPathMatrix[i][k] + shortestPathMatrix[k][j];
        }
      }
    }
  }
  return shortestPathMatrix;
}

std::vector<std::vector<int>> s21::GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
  int size = static_cast<int>(adjacencyMatrix.size());
  std::vector<std::vector<int>> resMatrix(size, std::vector<int>(size, 0));
  std::vector<bool> vertexes(size, false);
  vertexes[0] = true;
  int cnt_of_vertex = 1;
  while (cnt_of_vertex != size) {
    int x, y;
    int min = std::numeric_limits<int>::max();
    for (int i = 0; i < size; i++) {
      if (vertexes[i]) {
        for (int j = 0; j < size; j++) {
          if (!vertexes[j] && adjacencyMatrix[i][j]) {
            if (min > adjacencyMatrix[i][j]) {
              min = adjacencyMatrix[i][j];
              y = i;
              x = j;
            }
          }
        }
      }
    }
    vertexes[x] = true;
    resMatrix[y][x] = min;
    cnt_of_vertex++;
  }
  return resMatrix;
}

s21::TsmResult s21::GraphAlgorithms::SolveTravelingSalesmanProblem(
    s21::Graph &graph) {
  AntAlgorithm ant{graph};
  return ant.getMinPath();
}

// Ant Algorithm

s21::AntAlgorithm::AntAlgorithm(s21::Graph &graph) : graph{graph} {}

s21::TsmResult s21::AntAlgorithm::getMinPath() {
  std::vector<std::vector<int>> adjacencyMatrix(graph.getAdjacencyMatrix());
  int size(adjacencyMatrix.size());
  std::vector<std::vector<double>> tau(size,
                                       std::vector<double>(size, Pheromone));

  s21::TsmResult result{};
  for (int i{}; i < 100; i++) {
    std::vector<TsmResult> waysAnts{};
    for (int index{}; index < size; index++) {
      TsmResult wayAnt = getWayOfAnt(tau, index);
      waysAnts.push_back(wayAnt);
      if (wayAnt.vertices.size() == adjacencyMatrix.size() + 1 &&
          (wayAnt.distance < result.distance || !result.distance)) {
        result.distance = wayAnt.distance;
        result.vertices.clear();
        result.vertices = wayAnt.vertices;
      }
    }
    updatePheromone(tau, waysAnts);
  }
  if (result.distance == 0) {
    throw std::logic_error("The solution of the problem is impossible");
  }
  for (size_t i{}; i < result.vertices.size(); i++) {
    result.vertices[i] += 1;
  }
  if (result.vertices.size() == adjacencyMatrix.size() + 1) {
    normalizeResult(result.vertices);
  }
  return result;
}

double s21::AntAlgorithm::getRandom() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  return dis(gen);
}

s21::TsmResult s21::AntAlgorithm::getWayOfAnt(
    std::vector<std::vector<double>> &tau, int index) {
  std::vector<std::vector<int>> adjacencyMatrix(graph.getAdjacencyMatrix());
  std::vector<bool> vertices(adjacencyMatrix.size(), false);

  s21::TsmResult result{};
  int start_index = index;
  result.vertices.push_back(index);
  vertices[index] = true;

  std::vector<int> freeVertices = getFreeVertices(vertices, index);
  while (freeVertices.size() > 0) {
    std::vector<double> probabilityVector =
        getProbability(freeVertices, tau, index);
    int next_vertex = getNextVertex(freeVertices, probabilityVector);
    result.distance += adjacencyMatrix[index][next_vertex];
    result.vertices.push_back(next_vertex);
    vertices[next_vertex] = true;
    index = next_vertex;
    freeVertices = getFreeVertices(vertices, index);
  }
  result.distance += adjacencyMatrix[index][start_index];
  if (adjacencyMatrix[index][start_index] > 0) {
    result.vertices.push_back(start_index);
  }
  return result;
}

std::vector<int> s21::AntAlgorithm::getFreeVertices(std::vector<bool> &vertices,
                                                    int index) {
  std::vector<std::vector<int>> adjacencyMatrix(graph.getAdjacencyMatrix());
  std::vector<int> result;
  for (size_t j{}; j < adjacencyMatrix.size(); j++) {
    if (adjacencyMatrix[index][j] > 0 && !vertices[j]) {
      result.push_back(j);
    }
  }
  return result;
}

std::vector<double> s21::AntAlgorithm::getProbability(
    std::vector<int> &freeVertices, std::vector<std::vector<double>> &tau,
    int index) {
  std::vector<std::vector<int>> adjacencyMatrix(graph.getAdjacencyMatrix());
  std::vector<double> result;

  double summ{};
  for (const auto &j : freeVertices) {
    if (adjacencyMatrix[index][j]) {
      double nu = 1.0 / adjacencyMatrix[index][j];
      double probability = std::pow(tau[index][j], Alpha) * std::pow(nu, Beta);
      result.push_back(probability);
      summ += probability;
    }
  }
  for (size_t i{}; i < result.size(); i++) {
    result[i] /= summ;
  }
  return result;
}

int s21::AntAlgorithm::getNextVertex(std::vector<int> &freeVertices,
                                     std::vector<double> &probabilityVector) {
  double rand = getRandom();
  double summ = 0.0;
  size_t counter = 0;
  for (; counter < probabilityVector.size(); counter++) {
    summ += probabilityVector[counter];
    if (rand <= summ) {
      break;
    }
  }

  return freeVertices[counter];
}

void s21::AntAlgorithm::updatePheromone(std::vector<std::vector<double>> &tau,
                                        std::vector<s21::TsmResult> &waysAnts) {
  for (size_t i{}; i < tau.size(); i++) {
    for (size_t j{}; j < tau.size(); j++) {
      tau[i][j] *= (1 - Evaporation);
    }
  }
  for (size_t i{}; i < waysAnts.size(); i++) {
    double L = waysAnts[i].distance;
    double delta_t = Q / L;
    std::vector<int> way_ant = waysAnts[i].vertices;

    for (size_t j{1}; j < way_ant.size(); j++) {
      int x1 = way_ant[j - 1];
      int x2 = way_ant[j];
      tau[x1][x2] += delta_t;
      tau[x2][x1] += delta_t;
    }
  }
}

void s21::AntAlgorithm::normalizeResult(std::vector<int> &result) {
  std::vector<int> tmp(result.size(), 0);
  int index_1{};
  for (size_t i{}; i < result.size(); i++) {
    if (result[i] == 1) {
      index_1 = i;
      break;
    }
  }

  if (index_1 != 0) {
    int index_tmp = 0;
    for (int i{index_1}; i < (int)result.size() - 1; i++) {
      tmp[index_tmp++] = result[i];
    }
    for (int i{}; i < index_1; i++) {
      tmp[index_tmp++] = result[i];
    }
    tmp[index_tmp] = 1;
    result = tmp;
  }
}
