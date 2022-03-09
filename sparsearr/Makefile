all: sparsearr

CXX = g++
CXXFLAGS = -std=c++20 -O2 -I ~/include -L ~/lib 
EXTRAS = -lsdsl -ldivsufsort -ldivsufsort64

sparsearr: sparsearr.cpp
	$(CXX) $(CXXFLAGS) -o sparsearr $< $(EXTRAS)

clean:
	rm -f sparsearr.o sparsearr
