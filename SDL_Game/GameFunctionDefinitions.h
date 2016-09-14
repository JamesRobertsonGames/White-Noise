#pragma once

#include "SDL/SDL2-2.0.3/include/SDL.h"
#include "SDL_Operations.h"
#include "Bullet.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include "PowerUp.h"

void update(SDL_Renderer * Renderer, SDL_Rect &destRect, SDL_Texture * texture);
void updateNoClear(SDL_Renderer * Renderer, SDL_Rect &destRect, SDL_Texture * texture);
void destroy(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer);
void splashScreen(SDL_Renderer* renderer);
void homeMenu(SDL_Renderer* renderer);
void gameLoop();
