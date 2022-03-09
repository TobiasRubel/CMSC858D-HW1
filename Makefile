all: main

CXX = g++
CXXFLAGS = -std=c++20 -O2 -I ~/include -L ~/lib 
EXTRAS = -lsdsl -ldivsufsort -ldivsufsort64

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main $< $(EXTRAS)

clean:
	rm -f main.o main
