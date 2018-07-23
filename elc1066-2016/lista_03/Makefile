CXX = clang
CXXFLAGS = -g -Wall

all: main

main.o: main.c lista.h
lista.o: lista.c lista.h

main: main.o lista.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f main *.o
