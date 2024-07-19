#include "tests.hpp"

TEST(DepthFirstSearch, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.DepthFirstSearch(gr, 1);
  std::vector<int> right{1, 2, 3, 4, 5, 6};
  EXPECT_TRUE(res == right);
}

TEST(DepthFirstSearch, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.DepthFirstSearch(gr, 2);
  std::vector<int> right{2, 1, 5, 4, 3, 6};
  EXPECT_TRUE(res == right);
}

TEST(DepthFirstSearch, TEST_3) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.DepthFirstSearch(gr, 6);
  std::vector<int> right{6, 2, 1, 5, 4, 3};
  EXPECT_TRUE(res == right);
}

TEST(DepthFirstSearch, TEST_4) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  EXPECT_THROW(alg.DepthFirstSearch(gr, -1), std::invalid_argument);
  EXPECT_THROW(alg.DepthFirstSearch(gr, 7), std::invalid_argument);
}

TEST(BreadthFirstSearch, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.BreadthFirstSearch(gr, 1);
  std::vector<int> right{1, 2, 5, 3, 6, 4};
  EXPECT_TRUE(res == right);
}

TEST(BreadthFirstSearch, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.BreadthFirstSearch(gr, 2);
  std::vector<int> right{2, 1, 3, 6, 5, 4};
  EXPECT_TRUE(res == right);
}

TEST(BreadthFirstSearch, TEST_3) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<int> res = alg.BreadthFirstSearch(gr, 6);
  std::vector<int> right{6, 2, 3, 4, 5, 1};
  EXPECT_TRUE(res == right);
}

TEST(BreadthFirstSearch, TEST_4) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  EXPECT_THROW(alg.BreadthFirstSearch(gr, -1), std::invalid_argument);
  EXPECT_THROW(alg.BreadthFirstSearch(gr, 7), std::invalid_argument);
}

TEST(GetShortestPathBetweenVertices, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(gr, 1, 6), 7);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(gr, 1, 3), 12);
  EXPECT_THROW(alg.GetShortestPathBetweenVertices(gr, 0, 2),
               std::invalid_argument);
  EXPECT_THROW(alg.GetShortestPathBetweenVertices(gr, 3, 7),
               std::invalid_argument);
  EXPECT_THROW(alg.GetShortestPathBetweenVertices(gr, -3, 9),
               std::invalid_argument);
}

TEST(GetShortestPathBetweenVertices, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph11.txt");

  s21::GraphAlgorithms alg;
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(gr, 4, 10), 37);
  EXPECT_EQ(alg.GetShortestPathBetweenVertices(gr, 1, 10), 38);
  EXPECT_THROW(alg.GetShortestPathBetweenVertices(gr, 0, 2),
               std::invalid_argument);
  EXPECT_THROW(alg.GetShortestPathBetweenVertices(gr, 2, 12),
               std::invalid_argument);
}

TEST(GetShortestPathsBetweenAllVertices, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<std::vector<int>> res =
      alg.GetShortestPathsBetweenAllVertices(gr);
  std::vector<std::vector<int>> right{
      {0, 7, 12, 12, 4, 7},  {7, 0, 5, 11, 5, 2}, {12, 5, 0, 11, 9, 6},
      {12, 11, 11, 0, 8, 9}, {4, 5, 9, 8, 0, 3},  {7, 2, 6, 9, 3, 0}};
  for (std::size_t i = 0; i < res.size(); i++) {
    for (std::size_t j = 0; j < res.size(); j++) {
      EXPECT_EQ(res[i][j], right[i][j]);
    }
  }
}

TEST(GetShortestPathsBetweenAllVertices, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph11.txt");

  s21::GraphAlgorithms alg;
  std::vector<std::vector<int>> res =
      alg.GetShortestPathsBetweenAllVertices(gr);
  std::vector<std::vector<int>> right{{0, 2, 3, 3, 8, 9, 16, 26, 37, 38},
                                      {2, 0, 1, 5, 6, 11, 14, 24, 35, 36},
                                      {3, 1, 0, 4, 5, 10, 13, 23, 34, 35},
                                      {3, 5, 4, 0, 9, 6, 15, 25, 36, 37},
                                      {8, 6, 5, 9, 0, 7, 8, 18, 29, 30},
                                      {9, 11, 10, 6, 7, 0, 9, 19, 30, 31},
                                      {16, 14, 13, 15, 8, 9, 0, 10, 21, 22},
                                      {26, 24, 23, 25, 18, 19, 10, 0, 11, 12},
                                      {37, 35, 34, 36, 29, 30, 21, 11, 0, 13},
                                      {38, 36, 35, 37, 30, 31, 22, 12, 13, 0}};
  for (std::size_t i = 0; i < res.size(); i++) {
    for (std::size_t j = 0; j < res.size(); j++) {
      EXPECT_EQ(res[i][j], right[i][j]);
    }
  }
}

TEST(GetLeastSpanningTree, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph1.txt");

  s21::GraphAlgorithms alg;
  std::vector<std::vector<int>> res = alg.GetLeastSpanningTree(gr);
  std::vector<std::vector<int>> right{{0, 0, 0, 0, 4, 0}, {0, 0, 5, 0, 0, 0},
                                      {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 8, 0, 3}, {0, 2, 0, 0, 0, 0}};
  for (std::size_t i = 0; i < res.size(); i++) {
    for (std::size_t j = 0; j < res.size(); j++) {
      EXPECT_EQ(res[i][j], right[i][j]);
    }
  }
}

TEST(GetLeastSpanningTree, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph11.txt");

  s21::GraphAlgorithms alg;
  std::vector<std::vector<int>> res = alg.GetLeastSpanningTree(gr);
  std::vector<std::vector<int>> right{
      {0, 2, 0, 3, 0, 0, 0, 0, 0, 0},  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 5, 0, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 6, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 8, 0, 0, 0},  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 10, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 11, 12},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  for (std::size_t i = 0; i < res.size(); i++) {
    for (std::size_t j = 0; j < res.size(); j++) {
      EXPECT_EQ(res[i][j], right[i][j]);
    }
  }
}

TEST(SolveTravelingSalesmanProblem, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph2.txt");

  s21::GraphAlgorithms alg;
  s21::TsmResult res = alg.SolveTravelingSalesmanProblem(gr);
  EXPECT_TRUE(res.distance == 96);
}

TEST(SolveTravelingSalesmanProblem, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph3.txt");

  s21::GraphAlgorithms alg;
  s21::TsmResult res = alg.SolveTravelingSalesmanProblem(gr);
  EXPECT_TRUE(res.distance == 46);
}

TEST(SolveTravelingSalesmanProblem, TEST_3) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph4.txt");

  s21::GraphAlgorithms alg;
  s21::TsmResult res = alg.SolveTravelingSalesmanProblem(gr);
  EXPECT_TRUE(res.distance == 46);
}

TEST(SolveTravelingSalesmanProblem, TEST_4) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph5.txt");

  s21::GraphAlgorithms alg;
  s21::TsmResult res = alg.SolveTravelingSalesmanProblem(gr);
  EXPECT_TRUE(res.distance == 56);
}

TEST(SolveTravelingSalesmanProblem, TEST_5) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph6.txt");

  s21::GraphAlgorithms alg;

  EXPECT_THROW(alg.SolveTravelingSalesmanProblem(gr), std::logic_error);
}

TEST(SolveTravelingSalesmanProblem, TEST_6) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph7.txt");

  s21::GraphAlgorithms alg;
  s21::TsmResult res = alg.SolveTravelingSalesmanProblem(gr);
  EXPECT_TRUE(res.distance == 28);
}

TEST(Graph, TEST_1) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph2.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 0);
  EXPECT_TRUE(gr.isWeightedGraph() == 1);
}

TEST(Graph, TEST_2) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph3.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 0);
  EXPECT_TRUE(gr.isWeightedGraph() == 1);
}

TEST(Graph, TEST_3) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph4.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 1);
  EXPECT_TRUE(gr.isWeightedGraph() == 1);
}

TEST(Graph, TEST_4) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph8.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 0);
  EXPECT_TRUE(gr.isWeightedGraph() == 0);
}

TEST(Graph, TEST_5) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph9.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 0);
  EXPECT_TRUE(gr.isWeightedGraph() == 1);
}

TEST(Graph, TEST_6) {
  s21::Graph gr{};
  gr.LoadGraphFromFile("unit_tests/examples/graph10.txt");

  EXPECT_TRUE(gr.isDirectedGraph() == 0);
  EXPECT_TRUE(gr.isWeightedGraph() == 0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
