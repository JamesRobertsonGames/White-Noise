#pragma once
#include "GameFunctionDefinitions.h"
#include <vector>

namespace gam
{
	class bullet
	{
	public:
		bullet();
		void spawnBullet(int x, int y);
		void moveBullets();
		void drawBullets(SDL_Renderer * Renderer, SDL_Texture *Bullet);
		void eraseBullets();
		void throwBullets(uint8_t index);
		SDL_Rect getBullet(uint8_t index);
		uint8_t amountOfBullets();
	private:
		std::vector<SDL_Rect> bullets;
		int8_t velocity;
	};
}
