/*!
*  \brief     Enemy Class.
*  \details   This class is to handle the enemies, how they move, collision.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/

#include "Enemy.h"
#include <cstdlib>

//----------------------------------------------------------------------------------------------------//

/// All of the variables are initilaised in the class
gam::enemy::enemy()
{
	velocity = 14;
	patternID = 0;
	positionIncrement = 0;

	// Initilise all of the pre set patterns to the level
	One[0].x = 700;
	One[0].y = -700;
	One[1].x = 550;
	One[1].y = -850;

	One[2].x = 700;
	One[2].y = -850;
	One[3].x = 850;
	One[3].y = -850;

	One[4].x = 450;
	One[4].y = -1000;
	One[5].x = 625;
	One[5].y = -1000;

	One[6].x = 775;
	One[6].y = -1000;
	One[7].x = 925;
	One[7].y = -1000;

	for (size_t i = 0; i < 8; i++)
	{
		Two[i].x = 300 - positionIncrement;
		Two[i].y = -100 - positionIncrement;
		positionIncrement += 130;
	}

	positionIncrement = 0;

	for (size_t i = 0; i < 8; i++)
	{
		Three[i].x = 1500 + positionIncrement;
		Three[i].y = -200 + positionIncrement;
		positionIncrement += 130;
	}

	Four[0].x = 910;
	Four[0].y = -100;

	Four[1].x = 780;
	Four[1].y = -230;

	Four[2].x = 650;
	Four[2].y = -360;

	Four[3].x = 520;
	Four[3].y = -490;

	Four[4].x = 1040;
	Four[4].y = -230;

	Four[5].x = 1170;
	Four[5].y = -360;

	Four[6].x = 1300;
	Four[6].y = -490;
}


void gam::enemy::spawnPattern()
{
	randomPattern = rand() % 4;

	switch (randomPattern)
	{
	case 0:
		for (size_t i = 0; i < 8; i++)
		{
			spawnEnemy(One[i].x, One[i].y);
			patternID = 0;
		}
		break;
	case 1:
		for (size_t i = 0; i < 8; i++)
		{
			spawnEnemy(Two[i].x, Two[i].y);
			patternID = 1;
		}
		break;
	case 2:
		for (size_t i = 0; i < 8; i++)
		{
			spawnEnemy(Three[i].x, Three[i].y);
			patternID = 2;
		}
		break;
	case 3:
		for (size_t i = 0; i < 8; i++)
		{
			spawnEnemy(Four[i].x, Four[i].y);
			patternID = 3;
		}
		break;
	}
}

//uint8_t enemy::getPatternID()
//{
//	return patternID;
//}

//----------------------------------------------------------------------------------------------------//

/// Spawn the enemy in a specific location
void gam::enemy::spawnEnemy(int x, int y)
{
	// Temp Rect to push to the vector
	SDL_Rect temp;

	// Assign the values to the ones that were passed through
	temp.x = x;
	temp.y = y;

	// Push it to the vector
	enemies.push_back(temp);

	///int random = rand() % 800;
	/// Place different patterns here that spawn - Type
	/// Case statement here with random basing the outcome every 15 seconds (?) - That will be passed through - or called through main
}

//----------------------------------------------------------------------------------------------------//

/// Move the enemies
void gam::enemy::moveEnemyPatterns()
{
	switch (patternID)
	{
	case 0:
		for (size_t i = 0; i < enemies.size(); i++)
		{
			// Move the enemy "South - East"
			enemies[i].y += velocity;

			if (enemies[i].y > 4000)
			{
				eraseEnemy();
			}
		}
		break;
	case 1:
		// For loop to move each enemy
		for (size_t i = 0; i < enemies.size(); i++)
		{
			// Move the enemy "South - East"
			enemies[i].y += velocity;
			enemies[i].x += velocity;

			// If they're off screen delete them!
			if (enemies[i].y > 4000)
			{
				eraseEnemy();
			}
		}
		break;

	case 2:
		for (size_t i = 0; i < enemies.size(); i++)
		{
			// Move the enemy "South - East"
			enemies[i].y += velocity;
			enemies[i].x -= velocity;

			if (enemies[i].y > 4000)
			{
				eraseEnemy();
			}
		}
		break;
	case 3:
		for (size_t i = 0; i < enemies.size(); i++)
		{
			// Move the enemy "South - East"
			enemies[i].y += velocity;

			if (enemies[i].y > 4000)
			{
				eraseEnemy();
			}
		}
		break;
	}
}

//----------------------------------------------------------------------------------------------------//

// Draw the enemies on screen
void gam::enemy::drawEnemy(SDL_Renderer * Renderer, SDL_Texture *Bullet)
{
	// Loop through the vector of the enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		// Draw onto the screen
		SDL_QueryTexture(Bullet, NULL, NULL, &enemies[i].w, &enemies[i].h);
		SDL_RenderCopy(Renderer, Bullet, NULL, &enemies[i]);
	}
}

//----------------------------------------------------------------------------------------------------//

/// Check the collisions of each enemy to each bullet
bool gam::enemy::checkCollisions(SDL_Rect bullet)
{
	// Go through each enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		// Check with the bullet that has been passed through
		if (SDL_HasIntersection(&enemies[i], &bullet))
		{
			// If hit, Teleport enemy off screen
			enemies[i].x = 4000;
			return true;
		}
	}
	return false;
}

void gam::enemy::restartGame()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].y = 4500;
	}
}
bool gam::enemy::checkShipCollisions(SDL_Rect ship)
{
	// Go through each enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		// Check with the bullet that has been passed through
		if (SDL_HasIntersection(&enemies[i], &ship))
		{
			// If hit, Teleport enemy off screen
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------//

/// Erase each enemy when they're not needed
void gam::enemy::eraseEnemy()
{
	// Erase the start of the array
	enemies.erase(enemies.begin());
}
