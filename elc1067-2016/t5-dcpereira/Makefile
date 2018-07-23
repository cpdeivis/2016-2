
CXX = clang++
CXXFLAGS = -g -std=c++11 -Wall

all: principal

principal.o: principal.cpp sintaxe.hpp
sintaxe.o: sintaxe.cpp sintaxe.hpp

principal: principal.o sintaxe.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f principal *.o
