EXE = test.o
DEFINES = NONE # PTREE for tree printing
CXX = c++
SRC = test/BinarySearchTreeTest.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

all: $(EXE) docs

docs: 
		doxygen docs/Doxyfile

$(EXE): $(SRC)
		$(CXX) -g $< -o $(EXE) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

clean: 
		@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean