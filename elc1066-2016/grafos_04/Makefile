CXX = clang
CXXFLAGS = -g -Wall

all: main

main.o: main.c grafo.h
grafo.o: grafo.c grafo.h

main: main.o grafo.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f main *.o
