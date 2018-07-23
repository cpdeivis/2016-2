
CXX = clang++
CXXFLAGS = -g -std=c++11 -Wall

all: principal

principal.o: principal.cpp arvore.hpp
arvore.o: arvore.cpp arvore.hpp

principal: principal.o arvore.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f principal *.o
