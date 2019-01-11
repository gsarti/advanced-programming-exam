EXE = test.o
CXX = c++
SRC = test/BinarySearchTreeTest.cpp
CXXFLAGS = -std=c++11 -Wall -Wextra
IFLAGS = -I include

$(EXE): $(SRC)
		$(CXX) -g $< -o $(EXE) $(CXXFLAGS) $(IFLAGS)

clean: 
		@rm -fr *.o