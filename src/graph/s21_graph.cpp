#include "s21_graph.hpp"

s21::Graph::Graph() : adjacency_matrix{{}} {}

void s21::Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file{filename};
  std::string line;
  if (file) {
    getline(file, line);
    std::stringstream ss1{line};
    int size{};
    ss1 >> size;
    adjacency_matrix.clear();
    while (getline(file, line)) {
      std::stringstream ss2{line};
      std::vector<int> row{};
      int value{};
      while (ss2 >> value) {
        row.push_back(value);
      }
      adjacency_matrix.push_back(row);
    }
    if (!isCorrectMatrix()) throw std::logic_error("Incorrect matrix");
    file.close();
  } else {
    throw std::logic_error("Incorrect file");
  }
}

void s21::Graph::ExportGraphToDot(std::string filename) {
  bool isDirected = isDirectedGraph();
  bool isWeighted = isWeightedGraph();

  std::string gr{};
  std::string token{};
  std::string graphname{"example"};

  if (isDirected) {
    gr = "digraph";
    token = " -> ";
  } else {
    gr = "graph";
    token = " -- ";
  }
  filename += ".dot";
  std::ofstream file{filename};
  if (file) {
    file << gr << " " << graphname << "{" << std::endl;
    for (size_t i{}; i < adjacency_matrix.size(); i++) {
      int end{};
      if (isDirected) {
        end = adjacency_matrix.size();
      } else {
        end = i + 1;
      }
      for (int j{}; j < end; j++) {
        if (adjacency_matrix[i][j]) {
          file << "    " << i + 1 << token << j + 1;
          if (isWeighted) {
            file << " [weight=" << adjacency_matrix[i][j] << "]";
          }
          file << ";" << std::endl;
        }
      }
    }
    file << "}";
    file.close();
  }
}

std::vector<std::vector<int>> s21::Graph::getAdjacencyMatrix() {
  return adjacency_matrix;
}

bool s21::Graph::isConnectedGraph() {
  int count = adjacency_matrix.size();
  std::vector<bool> visited(count, false);
  s21::stack<int> dfs;
  dfs.push(0);

  while (!dfs.empty()) {
    int vertex = dfs.top();
    dfs.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      for (int i = 0; i < count; i++) {
        if (adjacency_matrix[vertex][i] != 0 && !visited[i]) {
          dfs.push(i);
        }
      }
    }
  }
  bool res = true;
  for (bool visit : visited) {
    if (!visit) {
      res = false;
      break;
    }
  }
  return res;
}

bool s21::Graph::isSquareMatrix() {
  int res = true;
  size_t rows{adjacency_matrix.size()};

  for (const auto& row : adjacency_matrix) {
    if (row.size() != rows) {
      res = false;
      break;
    }
  }
  if (rows < 2) res = false;

  return res;
}

bool s21::Graph::isNaturalWeights() {
  int res = true;
  // size_t rows{adjacency_matrix.size()};
  for (const auto& row : adjacency_matrix) {
    for (const auto& value : row) {
      if (value < 0) {
        res = false;
        break;
      }
    }
    if (!res) break;
  }
  return res;
}

bool s21::Graph::isDirectedGraph() {
  int size = adjacency_matrix.size();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (adjacency_matrix[i][j] != adjacency_matrix[j][i]) return true;
    }
  }
  return false;
}

bool s21::Graph::isWeightedGraph() {
  int size = adjacency_matrix.size();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (adjacency_matrix[i][j] > 1) return true;
    }
  }
  return false;
}

bool s21::Graph::isCorrectMatrix() {
  bool res = true;
  res = isSquareMatrix();
  if (res) res = isNaturalWeights();
  if (res) res = isConnectedGraph();
  return res;
}

#include <iostream>
void s21::Graph::printMatrix() {
  for (const auto& row : adjacency_matrix) {
    for (const auto& value : row) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
}
