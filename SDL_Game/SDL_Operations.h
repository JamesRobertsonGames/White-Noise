#pragma once
#include "SDL/SDL2-2.0.3/include/SDL.h" 
#include <iostream>
#include <stdint.h>

SDL_Window *window();
SDL_Renderer *renderer(SDL_Window *window);

namespace img
{
	class newImageLoad
	{
	public:
		newImageLoad(std::string file);
		SDL_Texture *convertToTexture(SDL_Renderer *Renderer);
	private:
		std::string filename;
		SDL_Surface *surface;
	}; 
}
