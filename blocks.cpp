#include <algorithm>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <time.h>



class Blocks {
private:
	int screenWidth;
	int screenHeight;
	struct Vector2f {
		float x, y;
	};
	struct Color {
		int r, g, b, a;
	};
	struct Block {
		Vector2f pos;
		Color color;
		bool moveable;
		friend bool operator==(Block const &a, Block const &b)
		{
			return a == b;
		}
	};
	std::vector<Block> border;
	std::vector<Block> blocks;
	std::vector<Block> current;
	std::vector<std::vector<Block>> preset;
public:
	void init(int width, int height) {
		screenWidth = width;
		screenHeight = height;
		preset = {
			// i shape
			{ { {(screenWidth / 12.0f) * 4, (screenWidth / 12.0f)}, {0, 255, 255, 255 }, true}, { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f)}, {0, 255, 255, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f)}, {0, 255, 255, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f)}, {0, 255, 255, 255 }, true} } ,
			// j shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f)}, {0, 0, 171, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {0, 0, 171, 255 }, true}, { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f) * 2}, {0, 0, 171, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f) * 2}, {0, 0, 171, 255 }, true} } ,
			// l shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f) * 2}, {255, 120, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {255, 120, 0, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f) * 2}, {255, 120, 0, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f)}, {255, 120, 0, 255 }, true} } ,
			// o shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f)}, {255, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f)}, {255, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f) * 2}, {255, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {255, 255, 0, 255 }, true} } ,
			// s shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f) * 2}, {0, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {0, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f)}, {0, 255, 0, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f)}, {0, 255, 0, 255 }, true} } ,
			// z shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f)}, {255, 0, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f)}, {255, 0, 0, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {255, 0, 0, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f) * 2}, {255, 0, 0, 255 }, true} } ,
			// t shape
			{ { {(screenWidth / 12.0f) * 5, (screenWidth / 12.0f)}, {205, 0, 205, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f)}, {205, 0, 205, 255 }, true}, { {(screenWidth / 12.0f) * 7, (screenWidth / 12.0f)}, {205, 0, 205, 255 }, true}, { {(screenWidth / 12.0f) * 6, (screenWidth / 12.0f) * 2}, {205, 0, 205, 255 }, true} }

			
		};
		srand(time(NULL));
		current = preset[rand() % 7];
		//border blocks

		//left
		for (int i = 0; i < 20; i++) {
			Block block;
			block.pos.x = 0;
			block.pos.y = i * (screenWidth / 12);
			block.color.r = 60;
			block.color.g = 60;
			block.color.b = 60;
			block.color.a = 255;
			block.moveable = false;
			border.push_back(block);
		}
		//bottom
		for (int i = 0; i < 12; i++) {
			Block block;
			block.pos.x = i * (screenWidth / 12);
			block.pos.y = screenHeight - (screenWidth / 12);
			block.color.r = 60;
			block.color.g = 60;
			block.color.b = 60;
			block.color.a = 255;
			block.moveable = false;
			border.push_back(block);
		}
		//right
		for (int i = 0; i < 20; i++) {
			Block block;
			block.pos.x = screenWidth - (screenWidth / 12);
			block.pos.y = i * (screenWidth / 12);
			block.color.r = 60;
			block.color.g = 60;
			block.color.b = 60;
			block.color.a = 255;
			block.moveable = false;
			border.push_back(block);
		}
		//top
		for (int i = 0; i < 12; i++) {
			Block block;
			block.pos.x = i * (screenWidth / 12);
			block.pos.y = 0;
			block.color.r = 60;
			block.color.g = 60;
			block.color.b = 60;
			block.color.a = 255;
			block.moveable = false;
			border.push_back(block);
		}
	};
	void draw(SDL_Renderer* renderer) {
		for (const Block &block : current) {
			SDL_SetRenderDrawColor(renderer, block.color.r, block.color.g, block.color.b, block.color.a);
			SDL_FRect rect = { block.pos.x, block.pos.y, screenWidth / 12, screenWidth / 12 };
			SDL_RenderFillRectF(renderer, &rect);
		}
		for (const Block &block : border) {
			SDL_SetRenderDrawColor(renderer, block.color.r, block.color.g, block.color.b, block.color.a);
			SDL_FRect rect = { block.pos.x, block.pos.y, screenWidth / 12, screenWidth / 12 };
			SDL_RenderFillRectF(renderer, &rect);
		}
		for (const Block &block : blocks) {
			SDL_SetRenderDrawColor(renderer, block.color.r, block.color.g, block.color.b, block.color.a);
			SDL_FRect rect = { block.pos.x, block.pos.y, screenWidth / 12, screenWidth / 12 };
			SDL_RenderFillRectF(renderer, &rect);
		}
	}
	void move(int x, int y) {
		for (Block &block : current) {
			if (block.moveable) {
				if (block.pos.x + x < 0 || block.pos.x + x > screenWidth - (screenWidth / 12)) {
					return;
				}
				if (block.pos.y + y < 0 || block.pos.y + y > screenHeight - (screenWidth / 12)) {
					return;
				}
				for (const Block &borderBlock : border) {
					if (block.pos.x + x == borderBlock.pos.x && block.pos.y + y == borderBlock.pos.y) {
						return;
					}
				}
				for (const Block &block2 : blocks) {
					if (block.pos.x + x == block2.pos.x && block.pos.y + y == block2.pos.y) {
						return;
					}
				}
			}
		}
		for (Block &block : current) {
			if (block.moveable) {
				block.pos.x += x;
				block.pos.y += y;
			}
		}
	}
	int events() {
		float y = current[0].pos.y;
		move(0, screenWidth / 12);
		if (current[0].pos.y == y) {
			add();
			return gameOver() ? -1 : check();
		}
		return 0;
	}
	void rotate() {
		bool rotate = current[0].color.r + current[0].color.g == 510 ? false : true;
		std::vector<Block> temp = current;
		float cx = current[1].pos.x;
		float cy = current[1].pos.y;
		for (Block &block : temp) {
			if (block.moveable) {
				float x = block.pos.x;
				float y = block.pos.y;
				float x2 = -(y - cy) + cx;
				float y2 = (x - cx) + cy;
				block.pos.x = x2;
				block.pos.y = y2;
				if (block.pos.x - (screenWidth / 12) < 0 || block.pos.x + (screenWidth / 12) > screenWidth || block.pos.y - (screenWidth / 12) < 0 || block.pos.y + (screenWidth / 12) > screenHeight) {
					rotate = false;
				}
				for (const Block& borderBlock : border) {
					if (block.pos.x == borderBlock.pos.x && block.pos.y == borderBlock.pos.y) {
						rotate = false;
					}
				}
				for (const Block& block2 : blocks) {
					if (block.pos.x == block2.pos.x && block.pos.y == block2.pos.y) {
						rotate = false;
					}
				}
			}
		}
		if (rotate) {
			current = temp;
		}
	};
	void add() {
		for (Block &block : current) {
			block.moveable = false;
			blocks.push_back(block);
		}
		current = preset[rand() % 7];
	};
	int check() {
		int lines = 0;
		for (int y = 0; y < screenHeight; y += screenWidth / 12) {
			int num = 10;
			for (const Block &block : blocks) {
				if (block.pos.y == y) {
					num--;
				}
			}
			if (num == 0) {
				lines++;
				blocks.erase(
					std::remove_if(blocks.begin(), blocks.end(), [&](Block const& block) {
						return block.pos.y == y;
						}),
					blocks.end());
				for (Block &block : blocks) {
					if (block.pos.y < y) {
						block.pos.y += screenWidth / 12;
					}
				}
			}
		}
		return lines;
	}
	int drop() {
		for (Block &block : current) {
			float y = 0;
			while (current[0].pos.y != y) {
				y = current[0].pos.y;
				move(0, screenWidth / 12);
			}
		}
		add();
		return gameOver() ? -1 : check();
	}
	bool gameOver() {
		for (const Block &block : blocks) {
			if (block.pos.y <= (screenWidth / 12) * 3) {
				return true;
			}
		}
		return false;
	}
};