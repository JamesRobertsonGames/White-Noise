/*!
*  \brief     Image Load Class.
*  \details   This class is to handle the Image Loading.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/

#include "SDL_Operations.h"

SDL_Rect initRect(int16_t x, int16_t y)
{
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	return tempRect;
}

SDL_Window *window()
{
	// Initialise the SDL - Check if it broke
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
	}

	// You can make a window! Set it to fullscreen
	SDL_Window *WINDOW = SDL_CreateWindow
		("White Noise V0.7",0, 0,0, 0,
		SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);

	// Return the window
	return WINDOW;
}

SDL_Renderer *renderer(SDL_Window *window)
{
	// Set the renderer with V-Sync - Return it
	SDL_Renderer *Render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return Render;
}

SDL_Texture *texture(SDL_Surface* iImage, SDL_Renderer* Renderer)
{
	// Make a Texture and return it
	SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer, iImage);
	return Texture;
}

img::newImageLoad::newImageLoad(std::string file)
{
	// Set the filename
	filename = file;

	// Set the file to the surface
	surface = SDL_LoadBMP(filename.c_str());

	// Always do the check for the most likely first to save time
	if (surface)
	{
		// Transparent for all of the cyan images
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xff));
		return;
	}
	// If not - Lets tell the user
	std::cout << "This hasn't worked m'dear" << std::endl;

	// Quit!
	SDL_Quit();
	return;
}


SDL_Texture *img::newImageLoad::convertToTexture(SDL_Renderer* Renderer)
{
	// Make a texture, free surface and retur
	SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_FreeSurface(surface);
	return Texture;
}