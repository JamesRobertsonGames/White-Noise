#pragma once

#include <SDL.h>

namespace gam
{
	class PowerUp
	{
	public:
		PowerUp();
		~PowerUp();
		void spawnPowerUp(int x, int y);
		void movePowerUp();
		void drawPowerUp(SDL_Renderer * Renderer, SDL_Texture *PowerUp);
		bool checkCollisions(SDL_Rect ship);
		void erasePowerUp();
	private:
		int8_t velocity;
		SDL_Rect PowerUpRect;
	};
}
