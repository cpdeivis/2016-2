CXX = clang
CXXFLAGS = -g -Wall

all: main

main.o: main.c arvore.h
arvore.o: arvore.c arvore.h

main: main.o arvore.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f main *.o
