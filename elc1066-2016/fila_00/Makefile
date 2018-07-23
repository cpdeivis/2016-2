CXX = clang
CXXFLAGS = -g -Wall

all: main

main.o: main.c fila.h
fila.o: fila.c fila.h

main: main.o fila.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f main *.o
