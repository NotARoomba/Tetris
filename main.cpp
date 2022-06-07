#include <iostream>
#include "game.cpp"


int main(int argc, char *argv[])
{
	std::cout << "Tetris!" << std::endl;
	Game game = Game();
	while (!game.over) {
		game.events();
		game.draw();
	}
	return 0;
}