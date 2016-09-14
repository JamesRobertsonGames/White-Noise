#include "GameFunctionDefinitions.h"

void gameLoop()
{
	// Init the Window
	SDL_Window *Window = window();

	// Init the Renderer
	SDL_Renderer *Renderer = renderer(Window);

	// Initilise the controller and its vibration
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;

	// Open the audio
//	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// Hide the cursor on screen
	SDL_ShowCursor(SDL_DISABLE);

	// timers for assets
	float bulletTimer = 0.0f;
	float enemyTimer = 0.0f;

	// Delta to time the game
	float deltaTs;

	// Bools set to default values
	bool leftMouseButtonDown = false;
	bool bossMode = false;
	bool collision = false;
	bool penetration = false;
	bool fireRateUp = false;
	bool powerupspawned = false;
	bool powerupspawned2 = false;
	bool death = false;
	bool pause = false;

	// Set the unsigned integers to default values
	uint8_t gameState = 1;
	uint8_t bulletAmount = 5;
	uint8_t score = 0;
	uint16_t enemySpawnRate = 100;

	// Load the Images
	img::newImageLoad testImage("Game\\Images\\image3.bmp");
	img::newImageLoad bullet1("Game\\Images\\bullet.bmp");
	img::newImageLoad enemy1("Game\\Images\\boundingBox.bmp");
	img::newImageLoad powerUp("Game\\Images\\powerUp.bmp");
	img::newImageLoad powerUp2("Game\\Images\\powerUp2.bmp");
	img::newImageLoad pauseScreen("Game\\Images\\pauseScreen.bmp");
	img::newImageLoad penatration("Game\\Images\\penatration.bmp");
	img::newImageLoad gameOver("Game\\Images\\gameOver.bmp");
	img::newImageLoad keyEsc("Game\\Images\\keyEsc.bmp");
	img::newImageLoad scoreGood("Game\\Images\\goodScore.bmp");
	img::newImageLoad scoreGreat("Game\\Images\\greatScore.bmp");
	img::newImageLoad scoreBad("Game\\Images\\badScore.bmp");
	
	// Convert to texture
	SDL_Texture *shipTexture = testImage.convertToTexture(Renderer);
	SDL_Texture *bulletTexture = bullet1.convertToTexture(Renderer);
	SDL_Texture *enemyTexture = enemy1.convertToTexture(Renderer);
	SDL_Texture *powerUpTexture = powerUp.convertToTexture(Renderer);
	SDL_Texture *powerUp2Texture = powerUp2.convertToTexture(Renderer);
	SDL_Texture *pauseScreenTexture = pauseScreen.convertToTexture(Renderer);
	SDL_Texture *penatrationTexture = penatration.convertToTexture(Renderer);
	SDL_Texture *gameOverTexture = gameOver.convertToTexture(Renderer);
	SDL_Texture *keyEscTexture = keyEsc.convertToTexture(Renderer);
	SDL_Texture *scoreGoodTexture = scoreGood.convertToTexture(Renderer);
	SDL_Texture *scoreGreatTexture = scoreGreat.convertToTexture(Renderer);
	SDL_Texture *scoreBadTexture = scoreBad.convertToTexture(Renderer);

	// initilise the Bullet, Enemy & Power up class
	gam::bullet Bullet;
	gam::enemy Enemy;
	gam::PowerUp Penetration;
	gam::PowerUp SpeedUp;

	// Maybe deleted the ticks
	uint32_t lastTime = SDL_GetTicks();

	// the current time (no idea if this is used either)
	uint32_t current;

	// Init our texture in a rectangle
	SDL_Rect shipRect = initRect(960, 1000);
	SDL_Rect pauseScreenRect = initRect(660, 340);
	SDL_Rect penatrationRect = initRect(10, 1030);
	SDL_Rect gameOverRect = initRect(0, 0);
	SDL_Rect keyEscRect = initRect(10, 10);
	SDL_Rect scoreGoodRect = initRect(1687, 885);
	SDL_Rect scoreGreatRect = initRect(1636,825);
	SDL_Rect scoreBadRect = initRect(1524,733);

	// Game Loop! (Update)
	bool go = true;
	while (go)
	{
		// When the game starts go into the splash screen...
		if (gameState == 1)
		{
			splashScreen(Renderer);
			gameState = 2;
		}

		// ...Then go into the menu
		if (gameState == 2)
		{
			homeMenu(Renderer);
			gameState = 3;
		}

		// Increase the bullet timer
		bulletTimer++;
		// Maybe deleted - current ticks
		current = SDL_GetTicks();
		// Oh god I have no idea
		deltaTs = (current - lastTime) / 1000.0f;
		// lul wut
		lastTime = current;

		// if the controller is not plugged in
		if (controllerConnection == false)
		{
			// Make a new event and poll it
			SDL_Event event;
			SDL_PollEvent(&event);

			// Switch the event type
			switch (event.type)
			{
				// if mouse is not pressed
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					leftMouseButtonDown = false;
				break;

				// If mouse is pressed
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					leftMouseButtonDown = true;
				if (event.button.button == SDL_BUTTON_RIGHT)
					leftMouseButtonDown = false;

				// When the mouse is moved
			case SDL_MOUSEMOTION:
				shipRect.x = event.motion.x - 60;
				shipRect.y = event.motion.y - 30;
				break;
			}
			// If the bullet timer is more than 5 shoot...
			if (bulletTimer > bulletAmount)
			{
				//... Only if the button is pressed
				if (leftMouseButtonDown)
				{
					Bullet.spawnBullet(shipRect.x, shipRect.y);
					bulletTimer = 0;
				}
			}
		}
		// If the controller is connected then use that!
		else
		{
			
		}
		// If this is out of the code then the game crashes I find.
		SDL_Event incomingEvent;

		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				// This means we have been asked to quit 
				go = false;
				break;
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					pause = true;
					break;
				}				
			}
		}

		// If the score is over 10 then show the "Good" image & increase how quick enemies spawns
		if (score > 10)
		{
			enemySpawnRate = 80;
			updateNoClear(Renderer, scoreGoodRect, scoreGoodTexture);
			
			// If the score is over 10 then show the "Great" image & increase how quick enemies spawns
			if (score > 20)
			{
				enemySpawnRate = 60;
				updateNoClear(Renderer, scoreGreatRect, scoreGreatTexture);
			}
		}
		
		// Increase the timer to spawn enemies
		enemyTimer++;

		// If the power ups are not spawn then spawn it! 
		if (!powerupspawned)
		{
			Penetration.spawnPowerUp(800, -rand() % 5500 - 300);
			powerupspawned = true;
		}

		if (!powerupspawned2)
		{
			SpeedUp.spawnPowerUp(300, -rand() % 2000 - 300);
			powerupspawned2 = true;
		}

		// Move the power ups each frame
		Penetration.movePowerUp();
		SpeedUp.movePowerUp();

		// Test collisions for each power up
		if (Penetration.checkCollisions(shipRect))
		{
			penetration = true;
		}

		if (SpeedUp.checkCollisions(shipRect))
		{
			fireRateUp = true;
		}

		// Test if the fire rate is up
		if (fireRateUp)
		{
			bulletAmount = 1;
		}

		// Test if the boss mode is on
		if (bossMode)
		{
			enemySpawnRate = 21;
			penetration = true;
			updateNoClear(Renderer, scoreBadRect, scoreBadTexture);
		}

		// Spawn if over the specified range
		if (enemyTimer > enemySpawnRate)
		{
			Enemy.spawnPattern();
			enemyTimer = 0;
		}

		Enemy.moveEnemyPatterns();

		// Move the bullets 
		Bullet.moveBullets();

		// Check the collisions
		for (uint8_t i = 0; i < Bullet.amountOfBullets(); i++)
		{
			collision = Enemy.checkCollisions(Bullet.getBullet(i));
			if (collision)
			{
				score += 1;
			}
			if (!penetration)
			{
				if (collision)
				{
					Bullet.throwBullets(i);
				}
			}
		}

		// Test if you are dead then save the result
		death = Enemy.checkShipCollisions(shipRect);

		// If the score is over 40 then BOSS MODE
		if (score > 40)
		{
			bossMode = true;
		}

		// When paused
		while (pause)
		{
			// Show pause graphic
			update(Renderer, pauseScreenRect, pauseScreenTexture);

			// Poll the event
			while (SDL_PollEvent(&incomingEvent))
			{
				switch (incomingEvent.type)
				{
				case SDL_QUIT:
					// This means we have been asked to quit 
					go = false;
					break;
				case SDL_KEYDOWN:
					switch (incomingEvent.key.keysym.sym)
					{

					// When you press escape it stops pausing
					case SDLK_ESCAPE:
						pause = false;
						break;

					// "E" Quits the game
					case SDLK_e:
						pause = false;
						go = false;

					}
				}
			}
		}

		// If penetration is true then show graphic
		if (penetration)
		{
			updateNoClear(Renderer, penatrationRect, penatrationTexture);
		}

		// Update the drawing

		// (Key Esc)
		updateNoClear(Renderer, keyEscRect, keyEscTexture);

		// (Player)
		update(Renderer, shipRect, shipTexture);

		// (Power ups)
		Penetration.drawPowerUp(Renderer, powerUpTexture);
		SpeedUp.drawPowerUp(Renderer, powerUp2Texture);

		// (Draw Bullets & Enemies)
		Bullet.drawBullets(Renderer, bulletTexture);
		Enemy.drawEnemy(Renderer, enemyTexture);
	
		while (death)
		{
			update(Renderer, gameOverRect, gameOverTexture);
			while (SDL_PollEvent(&incomingEvent))
			{
				switch (incomingEvent.type)
				{
				case SDL_QUIT:
					// This means we have been asked to quit 
					go = false;
					break;
				case SDL_KEYDOWN:
					switch (incomingEvent.key.keysym.sym)
					{
					case SDLK_ESCAPE:

						// Reset all the values
						Enemy.restartGame();
						gameState = 2;
						score = 0;
						enemySpawnRate = 100;
						bulletAmount = 5;
						bossMode = false;
						penetration = false;
						fireRateUp = false;
						death = false;
						powerupspawned = false;
						powerupspawned2 = false;
						shipRect = initRect(960, 1000);
						break;
					}
				}
			}
			
		}

		// Hold at 60FPS!
		if (deltaTs < (1.0f / 60.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 60.0f) - deltaTs)*1000.0f));
		}
	}
	// out of game loop so destroy assets
	destroy(shipTexture, Window, Renderer);

	SDL_DestroyTexture(shipTexture);
	SDL_DestroyTexture(bulletTexture);
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(powerUpTexture);
	SDL_DestroyTexture(powerUp2Texture);
	SDL_DestroyTexture(pauseScreenTexture);
	SDL_DestroyTexture(penatrationTexture);
	SDL_DestroyTexture(gameOverTexture);
	SDL_DestroyTexture(keyEscTexture);
	SDL_DestroyTexture(scoreGoodTexture);
	SDL_DestroyTexture(scoreGreatTexture);
	SDL_DestroyTexture(scoreBadTexture);

	// SDL Cleanup process
	SDL_Quit();
//	Mix_Quit();
}
