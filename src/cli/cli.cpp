#include "cli.hpp"

s21::CommandLineInterface::CommandLineInterface() : graph{}, algorithms{} {};

void s21::CommandLineInterface::run() {
  loadGraphFromFile();
  chooseAction();
}

void s21::CommandLineInterface::chooseAction() {
  while (true) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Choose action:\n  1. Load a graph\n  2. Print Depth first "
                 "search\n  3. Print Breadth First Search\n  4. Print Shortest "
                 "Path Between Vertices\n  5. Print Shortest Paths Between All "
                 "Vertices\n  6. Print Least Spanning Tree\n  7. Print Solve "
                 "Traveling Salesman Problem\n  8. Export to dot file\n";
    std::string choice;
    std::cin >> choice;

    if (choice == "1") {
      loadGraphFromFile();
    } else if (choice == "2") {
      printDepthFirstSearch();
    } else if (choice == "3") {
      printBreadthFirstSearch();
    } else if (choice == "4") {
      printShortestPathBetweenVertices();
    } else if (choice == "5") {
      printShortestPathsBetweenAllVertices();
    } else if (choice == "6") {
      printLeastSpanningTree();
    } else if (choice == "7") {
      printSolveTravelingSalesmanProblem();
    } else if (choice == "8") {
      exportToDotFIle();
    } else if (choice == "Exit") {
      break;
    }
  }
}

void s21::CommandLineInterface::loadGraphFromFile() {
  while (true) {
    std::cout << "Enter the path to the file. example: files/graph.txt\n";
    std::string path;
    std::cin >> path;
    try {
      graph.LoadGraphFromFile(path);
      break;
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }
  }
}

void s21::CommandLineInterface::printDepthFirstSearch() {
  std::cout << "Enter the start vertex\n";
  int start_vertex{};
  std::cin >> start_vertex;
  try {
    std::vector<int> res = algorithms.DepthFirstSearch(graph, start_vertex);
    for (const auto& val : res) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::printBreadthFirstSearch() {
  std::cout << "Enter the start vertex\n";
  int start_vertex{};
  std::cin >> start_vertex;
  try {
    std::vector<int> res = algorithms.BreadthFirstSearch(graph, start_vertex);
    for (const auto& val : res) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::printSolveTravelingSalesmanProblem() {
  try {
    s21::TsmResult res = algorithms.SolveTravelingSalesmanProblem(graph);
    std::cout << "Distance = " << res.distance << std::endl;
    for (const auto& val : res.vertices) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::printShortestPathBetweenVertices() {
  std::cout << "Enter the start vertex\n";
  int vertex1;
  std::cin >> vertex1;
  int vertex2;
  std::cout << "Enter the end vertex\n";
  std::cin >> vertex2;
  try {
    int res =
        algorithms.GetShortestPathBetweenVertices(graph, vertex1, vertex2);
    std::cout << res;
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::printShortestPathsBetweenAllVertices() {
  try {
    std::vector<std::vector<int>> res =
        algorithms.GetShortestPathsBetweenAllVertices(graph);
    for (std::size_t i = 0; i < res.size(); i++) {
      for (std::size_t j = 0; j < res.size(); j++)
        std::cout << res[i][j] << ' ';
      std::cout << '\n';
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::printLeastSpanningTree() {
  try {
    std::vector<std::vector<int>> res = algorithms.GetLeastSpanningTree(graph);
    for (std::size_t i = 0; i < res.size(); i++) {
      for (std::size_t j = 0; j < res.size(); j++)
        std::cout << res[i][j] << ' ';
      std::cout << '\n';
    }
    std::cout << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void s21::CommandLineInterface::exportToDotFIle() {
  std::cout << "Enter filename. example: graph_example\n";
  std::string filename;
  std::cin >> filename;
  graph.ExportGraphToDot(filename);
}
