all: game.cpp blocks.cpp main.cpp
	g++ -o ./Tetris game.cpp blocks.cpp main.cpp -lSDL2 -lSDL2_ttf
	./Tetris