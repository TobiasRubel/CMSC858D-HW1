all: rank

CXX = g++
CXXFLAGS = -std=c++11 -O2 -I ~/include -L ~/lib 
EXTRAS = -lsdsl -ldivsufsort -ldivsufsort64

rank: rank.cpp
	$(CXX) $(CXXFLAGS) -o bvrank $< $(EXTRAS)

clean:
	rm -f bvrank.o bvrank
