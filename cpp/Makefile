EXE = test.o
DEFINES = NONE
CXX = c++
SRC = test/BinarySearchTreeTest.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include
DFLAGS = -D $(DEFINES)

$(EXE): $(SRC)
		$(CXX) -g $< -o $(EXE) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

clean: 
		@rm -fr *.o

.PHONY: clean