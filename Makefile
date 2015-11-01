all: main

CFLAGS= -Wall -std=c++11

debug: CFLAGS= -Wall -std=c++11 -g
debug: main

main: GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o
	g++ GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o -o main -lGL -lGLU -lglut -L. $(CFLAGS)

GLUTMain.o: GLUTMain.cpp
	g++ -c GLUTMain.cpp -lGL -lGLU -lglut $(CFLAGS)

cBicho.o: cBicho.cpp cBicho.h
	g++ -c cBicho.cpp $(CFLAGS)

cData.o: cData.cpp cData.h
	g++ -c cData.cpp $(CFLAGS)

cPlayer.o: cPlayer.cpp cPlayer.h
	g++ -c cPlayer.cpp $(CFLAGS)

cScene.o: cScene.cpp cScene.h
	g++ -c cScene.cpp $(CFLAGS)

cGame.o: cGame.cpp cGame.h
	g++ -c cGame.cpp $(CFLAGS)

cTexture.o: cTexture.cpp cTexture.h
	g++ -c cTexture.cpp $(CFLAGS)

clean:
	rm -f *.o main
