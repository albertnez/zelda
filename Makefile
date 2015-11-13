all: main

CFLAGS= -Wall -std=c++11
SOURCES := ${wildcard *.cpp}
OBJECTS := ${SOURCES:.cpp=.o}
debug: CFLAGS= -Wall -std=c++11 -g
debug: main

main: $(OBJECTS)
	g++ $(OBJECTS) -o main -lGL -lGLU -lglut -L. $(CFLAGS)

.cpp.o:
	g++ $(CFLAGS) $< -c -o $@

clean:
	rm -f *.o main
