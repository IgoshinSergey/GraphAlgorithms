CPP=g++
CFLAGS=-Wall -Werror -Wextra -Wpedantic
STANDART=-std=c++17
GTEST=-lgtest

S21_QUEUE=containers/s21_queue.cpp
S21_STACK=containers/s21_stack.cpp

LIBS=*.a

GRAPH=graph/s21_graph.cpp
GRAPH_ALGORITHMS = graph_algorithms/s21_graph_algorithms.cpp

all: interface

s21_stack:
	g++ $(S21_STACK) -c
	ar rcs s21_stack.a s21_stack.o
	rm -rf s21_stack.o

s21_queue:
	g++ $(S21_QUEUE) -c
	ar rcs s21_queue.a s21_queue.o
	rm -rf s21_queue.o

s21_graph:
	g++ $(GRAPH) -c
	ar rcs s21_graph.a s21_graph.o
	rm -rf s21_graph.o


s21_graph_algorithms:
	g++ $(GRAPH_ALGORITHMS) -c
	ar rcs s21_graph_algorithms.a s21_graph_algorithms.o
	rm -rf s21_graph_algorithms.o

tests: clean
	$(CPP) $(CFLAGS) $(STANDART) -c $(GRAPH) $(GRAPH_ALGORITHMS) $(S21_QUEUE) $(S21_STACK) unit_tests/*.cpp $(GTEST) 
	$(CPP) $(CFLAGS) $(STANDART) *.o -o unit_test $(GTEST) 
	./unit_test

interface: clean s21_stack s21_queue s21_graph s21_graph_algorithms
	$(CPP) $(CFLAGS) $(STANDART) -c cli/*.cpp
	$(CPP) $(CFLAGS) $(STANDART) *.o $(LIBS) -o main
	./main

style:
	clang-format -i cli/*.* containers/*.* graph/*.* graph_algorithms/*.* unit_tests/*.*	
	clang-format -n cli/*.* containers/*.* graph/*.* graph_algorithms/*.* unit_tests/*.*

clean:
	@rm -rf \
	*.o *.a main unit_test
