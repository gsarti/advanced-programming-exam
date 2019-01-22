TEST = test.o
BENCHMARK = benchmark.o
DEFINES = NONE # PTREE for tree printing
CXX = c++
TESTSRC = test/BinarySearchTreeTest.cpp 
BENCHSRC = test/BinarySearchTreeBenchmark.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

all: $(TEST) $(BENCHMARK) docs

docs: 
	doxygen docs/Doxyfile

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(BENCHMARK): $(BENCHSRC)
	$(CXX) -g $< -o $(BENCHMARK) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)
clean: 
	@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean
