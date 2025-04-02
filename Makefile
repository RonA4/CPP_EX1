#===============================================================================
# Makefile for Graph Algorithms Project
# Email: ronamsalem4@gmail.com
# This Makefile supports:
# Compiling and running the main demo (make Main)
# Compiling and running all unit tests with doctest (make test)
# Checking for memory leaks with valgrind (make valgrind)
# Cleaning all compiled files (make clean)
#===============================================================================

CXX = g++
CXXFLAGS = -Wall -std=c++11 -I. -IAdjacencyList -IAlgorithms -IMyDataStructures -ITestAndException

#Source files
SRC = AdjacencyList/Graph.cpp \
      Algorithms/Algorithms.cpp \
      MyDataStructures/Queue.cpp \
      MyDataStructures/PriorityQueue.cpp \
      MyDataStructures/UnionFind.cpp

# Entry points
MAIN_SRC = TestAndException/main.cpp
TEST_SRC = TestAndException/test.cpp

# Object files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
SRC_OBJ = $(SRC:.cpp=.o)

#Executables
MAIN_EXE = Main
TEST_EXE = test_runner


# Build and run the demo from main.cpp
Main: $(MAIN_EXE)
	./$(MAIN_EXE)

$(MAIN_EXE): $(MAIN_OBJ) $(SRC_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@


#Build and run all unit tests using doctest

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(SRC_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Run valgrind to detect memory leaks during tests

valgrind: $(TEST_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)

# Compile .cpp files into .o object files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean all build artifacts
clean:
	rm -f $(MAIN_EXE) $(TEST_EXE) $(MAIN_OBJ) $(TEST_OBJ) $(SRC_OBJ)