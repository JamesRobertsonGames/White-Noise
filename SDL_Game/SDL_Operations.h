#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdint.h>
#include <Windows.h>

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
