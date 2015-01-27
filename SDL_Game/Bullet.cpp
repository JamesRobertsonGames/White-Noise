/*!
*  \brief     Bullet Class.
*  \details   This class is to handle the bullets to move, delete, spawn and move.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/

#include "Bullet.h"
#include "Enemy.h"

//----------------------------------------------------------------------------------------------------//

/// Initilise the variables
gam::bullet::bullet()
{
	velocity = 21;
}

//----------------------------------------------------------------------------------------------------//

/// Spawn the bullets
void gam::bullet::spawnBullet(int ships_x, int ships_y)
{
	// Create a temp Rect to push back
	SDL_Rect temp;

	// Assign the passed in values
	temp.x = ships_x + 70;
	temp.y = ships_y + 10;

	// Push it to the vector
	bullets.push_back(temp);
}

//----------------------------------------------------------------------------------------------------//

/// Move all the bullets
void gam::bullet::moveBullets()
{
	// Go through the Vector of Bullets
	for (size_t i = 0; i < bullets.size(); i++)
	{
		// Move with velocity
		bullets[i].y -= velocity;

		// Delete if off screen
		if (bullets[i].y < -10)
		{
			eraseBullets();
		}
	}
}

//----------------------------------------------------------------------------------------------------//

/// Draw the bullets on screen
void gam::bullet::drawBullets(SDL_Renderer * Renderer, SDL_Texture *Bullet)
{
	// Loop through each bullet
	for (size_t i = 0; i < bullets.size(); i++)
	{
		// Draw them to the renderer
		SDL_QueryTexture(Bullet, NULL, NULL, &bullets[i].w, &bullets[i].h);
		SDL_RenderCopy(Renderer, Bullet, NULL, &bullets[i]);
	}
}

//----------------------------------------------------------------------------------------------------//

/// Erase the bullets
void gam::bullet::eraseBullets()
{
	// Erase the beginning of the vector
	bullets.erase(bullets.begin());
}

void gam::bullet::throwBullets(uint8_t index)
{
	bullets[index].x = 2500;
}

//----------------------------------------------------------------------------------------------------//

/// Get the bullet (This is used to get location of bullets for collision)
SDL_Rect gam::bullet::getBullet(uint8_t index)
{
	// Return the bullet that has been requested
	return bullets[index];
}

//----------------------------------------------------------------------------------------------------//

/// Get the amount of bullets in the vector
uint8_t gam::bullet::amountOfBullets()
{
	// Set to temp variable and then return it
	uint8_t amount = (uint8_t)bullets.size();
	return amount;
}

//----------------------------------------------------------------------------------------------------//
