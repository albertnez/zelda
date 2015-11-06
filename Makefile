all: main

CFLAGS= -Wall -std=c++11

debug: CFLAGS= -Wall -std=c++11 -g
debug: main

main: GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o cMap.o cAnim.o cGUI.o cOctorok.o utils.o
	g++ GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o cMap.o cAnim.o cGUI.o cOctorok.o utils.o -o main -lGL -lGLU -lglut -L. $(CFLAGS)

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

cMap.o: cMap.cpp cMap.h
	g++ -c cMap.cpp $(CFLAGS)

cAnim.o: cAnim.cpp cAnim.h
	g++ -c cAnim.cpp $(CFLAGS)

cGUI.o: cGUI.cpp cGUI.h
	g++ -c cGUI.cpp $(CFLAGS)

cOctorok.o: cOctorok.cpp cOctorok.h
	g++ -c cOctorok.cpp $(CFLAGS)

utils.o: utils.h utils.cpp
	g++ -c utils.cpp $(CFLAGS)

clean:
	rm -f *.o main
