# builds the two test programs, -g and -Wall so valgrind has line numbers and we see warnings
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

all: rbt-tests rbt-first-step

rbt-tests: RedBlackTree.cpp RedBlackTreeTests.cpp RedBlackTree.h
	$(CXX) $(CXXFLAGS) RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

rbt-first-step: RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp RedBlackTree.h
	$(CXX) $(CXXFLAGS) RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o rbt-first-step

clean:
	rm -f rbt-tests rbt-first-step
