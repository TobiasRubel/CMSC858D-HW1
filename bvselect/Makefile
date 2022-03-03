all: select

CXX = g++
CXXFLAGS = -std=c++20 -O2 -I ~/include -L ~/lib 
EXTRAS = -lsdsl -ldivsufsort -ldivsufsort64

select: select.cpp
	$(CXX) $(CXXFLAGS) -o bvselect $< $(EXTRAS)

clean:
	rm -f bvselect.o bvselect
