#pragma once

#include <SDL.h>
#include <vector>

namespace gam
{
	class enemy
	{
	public:
		enemy();
		void spawnPattern();
		void spawnEnemy(int x, int y);
		void moveEnemyPatterns();
		void drawEnemy(SDL_Renderer * Renderer, SDL_Texture *Enemy);
		bool checkCollisions(SDL_Rect bullet);
		void restartGame();
		bool checkShipCollisions(SDL_Rect ship);
		void eraseEnemy();
	private:
		std::vector<SDL_Rect> enemies;
		int8_t velocity;
		int16_t positionIncrement;
		uint8_t randomPattern;
		uint8_t patternID;

		struct patternSpawn
		{
			int16_t x, y;
		}
		One[8], Two[8], Three[8], Four[7];
	};
}
