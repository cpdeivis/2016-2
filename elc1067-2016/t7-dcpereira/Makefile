
CXX = clang++
CXXFLAGS = -g -std=c++11 -Wall

all: principal

principal.o: principal.cpp

principal: principal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f principal *.o
