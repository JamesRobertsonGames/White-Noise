#include "GameFunctionDefinitions.h"

//----------------------------------------------------------------------------------------------------//

/// Updates all of the drawing functions
void update(SDL_Renderer * Renderer, SDL_Rect &destRect, SDL_Texture * texture)
{
	// Set the background colour of the screen
	SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);

	// Query the texture to get its original width and height
	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	//Copy texture memory to the renderer
	SDL_RenderCopy(Renderer, texture, NULL, &destRect);

	// Instruct Renderer to display onto the screen
	SDL_RenderPresent(Renderer);

	// Clear the entire screen to our selected colour
	SDL_RenderClear(Renderer);
}

/// Updates all of the drawing functions (Doesn't clear the screen)
void updateNoClear(SDL_Renderer * Renderer, SDL_Rect &destRect, SDL_Texture * texture)
{
	// Set the background colour of the screen
	SDL_SetRenderDrawColor(Renderer, 0xff, 0xff, 0xff, 0xff);

	// Query the texture to get its original width and height
	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	//Copy texture memory to the renderer
	SDL_RenderCopy(Renderer, texture, NULL, &destRect);
}

//----------------------------------------------------------------------------------------------------//

void destroy(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer)
{
	// Destroy Assets Here
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void helpScreen(SDL_Renderer * renderer)
{
	// Load Image w/ Initilisation
	img::newImageLoad helpScreen("Game\\Images\\HelpScreen.bmp");
	SDL_Texture *helpScreenTecture = helpScreen.convertToTexture(renderer);
	SDL_Rect helpScreenRect = initRect(0, 0);

	// Set the help screen to go
	bool go = true;
	while (go)
	{
		// Show the help screen image
		update(renderer, helpScreenRect, helpScreenTecture);

		// Make a new event and poll it
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		// When the mouse is pressed then check for a collision
		case SDL_MOUSEBUTTONDOWN:
			go = false;
			break;
		}
	}
}

void splashScreen(SDL_Renderer* renderer)
{
	// Load Image w/ Initilisation
	img::newImageLoad splashGraphic("Game\\Images\\Splash AHHHHHHHHH.bmp");
	SDL_Texture* splashTexture = splashGraphic.convertToTexture(renderer);
	SDL_Rect splashPosition = initRect(0, 0);

	// Render it for 200 cycles
	for (uint16_t i = 0; i < 200; i++)
	{
		// Display image here
		update(renderer, splashPosition, splashTexture);
	}
}

void homeMenu(SDL_Renderer* renderer)
{
	// Set the game to keep running
	bool go = true;

	// Load the audio class in
	aud::audio *testAudio = new aud::audio();
	
	// Set boundries (What and where audio is)
	testAudio->sfxSelect(false);
	testAudio->loadAudio("Three_Thousand.wav");

	// Play the song
	testAudio->playAudio();

	uint16_t timer = 300;
	int16_t randomx = rand() % 1600;
	int16_t randomy = rand() % 800;
	int16_t velocity = 13;

	// Set the class for the new image
	img::newImageLoad Title("Game\\Images\\WhiteNoiseTitle.bmp");
	img::newImageLoad playButton("Game\\Images\\playGame.bmp");
	img::newImageLoad cursor("Game\\Images\\cursor.bmp");
	img::newImageLoad helpButton("Game\\Images\\helpButton.bmp");
	img::newImageLoad squares("Game\\Images\\boundingBox.bmp");

	// Save to a Texture
	SDL_Texture* TitleTexture = Title.convertToTexture(renderer);
	SDL_Texture* pButtonTexture = playButton.convertToTexture(renderer);
	SDL_Texture* cursorTexture = cursor.convertToTexture(renderer);
	SDL_Texture *helpButtonTecture = helpButton.convertToTexture(renderer);
	SDL_Texture* squareTexture = squares.convertToTexture(renderer);

	// Set the Rectangle up
	SDL_Rect TitlePosition = initRect(400, 100);
	SDL_Rect pButtonPosition = initRect(400, 500);	
	SDL_Rect cursorPosition = initRect(-100, -500);
	SDL_Rect helpButtonRect = initRect(400, 850);
	SDL_Rect squareTimes[32];

	// Keep going until requested
	while (go)
	{
		// Increase Timer per framer
		timer++;

		// Spawn every time the timer is over 200
		if (timer > 200)
		{
			// Go through each squares
			for (size_t i = 0; i < 32; i++)
			{
				// Spawn them randomly 
				randomx = rand() % 1600;
				randomy = rand() % 1080;
				randomy -= (randomy * 2);

				// Place them there
				squareTimes[i].y = randomy;
				squareTimes[i].x = randomx;

				// Reset the timer
				timer = 0;
			}
		}
		// Inplement the Velocity for each Square
		for (size_t i = 0; i < 32; i++)
		{
			squareTimes[i].y += velocity;
		}
		// Make a new event and poll it
		SDL_Event event;
		SDL_PollEvent(&event);

		// Switch the event type
		switch (event.type)
		{
			// When the mouse is pressed then check for a collision
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && SDL_HasIntersection(&pButtonPosition, &cursorPosition))
				// If the collision is met then go out the menu
				go = false;
			if (event.button.button == SDL_BUTTON_LEFT && SDL_HasIntersection(&helpButtonRect, &cursorPosition))
				// If the collision is met then go out the menu
				helpScreen(renderer);
			cursorPosition.x = 2000;
			break;
		case SDL_MOUSEMOTION:
			cursorPosition.x = event.motion.x - 60;
			cursorPosition.y = event.motion.y - 30;
			break;
		}
		// Instruct Renderer to display onto the screen 
		// (Squares)
		for (size_t i = 0; i < 32; i++)
		{
			updateNoClear(renderer, squareTimes[i], squareTexture);
		}
		// (Title)
		updateNoClear(renderer, TitlePosition, TitleTexture);
		// (Play Button)
		updateNoClear(renderer, pButtonPosition, pButtonTexture);
		// (Help Button)
		updateNoClear(renderer, helpButtonRect, helpButtonTecture);
		// (Cursor)
		update(renderer, cursorPosition, cursorTexture);
	}
}