/*!
*  \brief     PowerUp Class.
*  \details   This class is to handle the powerups, how they move, collision.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/

#include "PowerUp.h"
#include <cstdlib>
#include <iostream>
//----------------------------------------------------------------------------------------------------//

/// All of the variables are initilaised in the class
gam::PowerUp::PowerUp()
{
	velocity = 6;
}

gam::PowerUp::~PowerUp()
{

}
//----------------------------------------------------------------------------------------------------//

/// Spawn the PowerUp in a specific location
void gam::PowerUp::spawnPowerUp(int x, int y)
{
	// Temp Rect to push to the vector
	SDL_Rect temp;

	// Assign the values to the ones that were passed through
	temp.x = x;
	temp.y = y;

	PowerUpRect = temp;

	///int random = rand() % 800;
	/// Place different patterns here that spawn - Type
	/// Case statement here with random basing the outcome every 15 seconds (?) - That will be passed through - or called through main
}

//----------------------------------------------------------------------------------------------------//

/// Move the enemies
void gam::PowerUp::movePowerUp()
{

	// Move the PowerUp "South - East"
	PowerUpRect.y += velocity;

	// If they're off screen delete them!
	if (PowerUpRect.y > 1700)
	{
		velocity = 0;
	}

}

//----------------------------------------------------------------------------------------------------//

// Draw the enemies on screen
void gam::PowerUp::drawPowerUp(SDL_Renderer * Renderer, SDL_Texture *Bullet)
{
	// Draw onto the screen
	SDL_QueryTexture(Bullet, NULL, NULL, &PowerUpRect.w, &PowerUpRect.h);
	SDL_RenderCopy(Renderer, Bullet, NULL, &PowerUpRect);
}

//----------------------------------------------------------------------------------------------------//

/// Check the collisions of each PowerUp to each bullet
bool gam::PowerUp::checkCollisions(SDL_Rect ship)
{
	// Check with the bullet that has been passed through
	if (SDL_HasIntersection(&PowerUpRect, &ship))
	{
		// If hit, Teleport PowerUp off screen
		PowerUpRect.y = 2000;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------//

/// Erase each PowerUp when they're not needed
void gam::PowerUp::erasePowerUp()
{
	// Erase the start of the array
	//enemies.erase(enemies.begin());
}
