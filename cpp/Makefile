EXE = test_methods.o
EXE1 = Benchmarck.o
DEFINES = NONE # PTREE for tree printing
CXX = c++
SRC = test/BinarySearchTreeTest_methods.cpp 
SRC1 = test/Benchmarck.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

all: $(EXE) $(EXE1) docs

docs: 
		doxygen docs/Doxyfile

$(EXE): $(SRC)
		$(CXX) -g $< -o $(EXE) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(EXE1): $(SRC1)
		$(CXX) -g $< -o $(EXE1) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)
clean: 
		@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean
