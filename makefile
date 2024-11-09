CXX = g++
CXXFLAGS =	-pthread	 -g -Wall

lizard: lizard.o
	$(CXX) $(CXXFLAGS) -o lizard	lizard.o

lizard.o: lizard.cpp
	$(CXX) $(CXXFLAGS) -c lizard.cpp

clean:
	rm -rf *.o lizard