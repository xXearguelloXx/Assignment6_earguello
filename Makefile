CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

main: main.o coordinate.o
	$(CXX) $(CXXFLAGS) -o main main.o coordinate.o

main.o: main.cpp coordinate.h
	$(CXX) $(CXXFLAGS) -c main.cpp

coordinate.o: coordinate.cpp coordinate.h
	$(CXX) $(CXXFLAGS) -c coordinate.cpp

clean:
	rm -f main *.o
