all: main

main: GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o
	g++ GLUTMain.o cBicho.o cData.o cPlayer.o cScene.o cGame.o cTexture.o -o main -lGL -lGLU -lglut -L.

GLUTMain.o: GLUTMain.cpp
	g++ -c GLUTMain.cpp -lGL -lGLU -lglut

cBicho.o: cBicho.cpp cBicho.h
	g++ -c cBicho.cpp

cData.o: cData.cpp cData.h
	g++ -c cData.cpp

cPlayer.o: cPlayer.cpp cPlayer.h
	g++ -c cPlayer.cpp

cScene.o: cScene.cpp cScene.h
	g++ -c cScene.cpp

cGame.o: cGame.cpp cGame.h
	g++ -c cGame.cpp

cTexture.o: cTexture.cpp cTexture.h
	g++ -c cTexture.cpp

clean:
	rm *.o
