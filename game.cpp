#include <string> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "blocks.cpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 840
#define FPS 60.0

class Game {
	SDL_Event e;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Blocks blocks = Blocks();
	Uint32 tick;
	Uint32 blockTick = SDL_GetTicks();
	int score = 0;
	int level = 0;
public:
	bool over = false;
	Game() {
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, 0);
		blocks.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	void events() {
		tick = SDL_GetTicks();
		if (SDL_GetTicks() - tick < (1000 / FPS)) SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
		std::cout << "FPS: " << 1000 / (SDL_GetTicks() - tick) << " BlockTicks: " << SDL_GetTicks() - blockTick << std::endl;
		if (SDL_GetTicks() - blockTick > 1000) {
			int n = blocks.events();
			n == -1 ? gameOver() : updateScore(n);
			blockTick = SDL_GetTicks();
		}
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				if (renderer) {
					SDL_DestroyRenderer(renderer);
				}
				if (window) {
					SDL_DestroyWindow(window);
				}
				SDL_Quit();
				exit(0);
			}
			if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_UP) {
					blocks.rotate();
				}
				if (e.key.keysym.sym == SDLK_DOWN) {
					blocks.move(0, (SCREEN_WIDTH / 12));
				}
				if (e.key.keysym.sym == SDLK_LEFT) {
					blocks.move(-1*(SCREEN_WIDTH / 12), 0);
				}
				if (e.key.keysym.sym == SDLK_RIGHT) {
					blocks.move((SCREEN_WIDTH / 12), 0);
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					int n = blocks.drop();
					n == -1 ? gameOver() : updateScore(n);
				}
			}
		}
	}
	void draw() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		blocks.draw(renderer);
		SDL_SetRenderDrawColor(renderer, 48, 48, 48, 255);
		for (int i = (SCREEN_WIDTH / 12); i < (SCREEN_WIDTH); i += SCREEN_WIDTH/12) {
			SDL_RenderDrawLineF(renderer, i, (SCREEN_WIDTH / 12), i, SCREEN_HEIGHT - (SCREEN_WIDTH / 12));
		}
		for (int i = (SCREEN_WIDTH / 12); i < SCREEN_HEIGHT; i += SCREEN_WIDTH / 12) {
			SDL_RenderDrawLineF(renderer, (SCREEN_WIDTH / 12), i, SCREEN_WIDTH - (SCREEN_WIDTH / 12), i);
		}
		displayText(renderer, "UP: rotate, LEFT: left, RIGHT: right, DOWN: move one down, SPACE: place instantly", SCREEN_WIDTH / 12, SCREEN_HEIGHT-(SCREEN_WIDTH / 12), 11);
		displayText(renderer, "Score: " + std::to_string(score), SCREEN_WIDTH / 12, 10, 20);
		displayText(renderer, "Level: " + std::to_string(level), SCREEN_WIDTH - ((SCREEN_WIDTH / 12) * 3), 10, 20);
		SDL_RenderPresent(renderer);

	}
	void gameOver() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		displayText(renderer, "Game Over", SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2, 40);
		SDL_RenderPresent(renderer);
		SDL_Delay(5000);
		over = true;
	}
	void updateScore(int lines) {
		score += lines == 1? 40 * (level + 1): lines == 2? 100 * (level + 1): lines == 3? 300 * (level + 1): lines == 4? 1200 * (level + 1): 0;
		if (score > level * 1000) {
			level++;
		}
	}
	void displayText(SDL_Renderer* renderer, std::string text, float x, float y, int size) {
		TTF_Font* font = TTF_OpenFont("./arial.ttf", size);
		SDL_Color textColor = { 255, 255, 255 };
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_Rect textRect = { static_cast<int>(x), static_cast<int>(y), textSurface->w, textSurface->h };
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
};