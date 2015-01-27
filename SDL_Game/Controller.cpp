/*!
*  \brief     Controller Class.
*  \details   This class is to handle the controller input through Xinput.
*  \author    James Robertson
*  \version   1.0a
*  \date      2014-2015
*  \copyright GNU Public License.
*/
#include "ControllerDefinitions.h"
#include <cmath>
#include "Bullet.h"



//----------------------------------------------------------------------------------------------------//

bool controllerIsConnected(XINPUT_STATE &controller, XINPUT_VIBRATION &vibration)
{
	// Store if the controller is connected
	DWORD dwResult;
	DWORD dvResult;

	// Zeros all memory values in the controller
	ZeroMemory(&controller, sizeof(XINPUT_STATE));

	// Get the current state of controller 1
	dwResult = XInputGetState(0, &controller);

	// Zeros all the memory values in the vibration modual
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// Set the state of the vibration moduel
	dvResult = XInputSetState(0, &vibration);

	// If it worked return true if not then its not connected
	if (dwResult == ERROR_SUCCESS && dvResult == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----------------------------------------------------------------------------------------------------//

void vibrate(double leftmotor, double rightmotor)
{
	// Create a new Vibraton 
	XINPUT_VIBRATION Vibration;

	// Set first num bytes to block of memory (I Have no clue)
	memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

	// Vibrate amount
	WORD leftVib = (WORD)(leftmotor*65535.0f);
	WORD rightVib = (WORD)(rightmotor*65535.0f);

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVib;
	Vibration.wRightMotorSpeed = rightVib;

	// Vibrate the controller
	XInputSetState((int)0, &Vibration);
}

//----------------------------------------------------------------------------------------------------//

void movement(SDL_Rect &player, XINPUT_STATE &state)
{
	// Make this into a class probably though I do not see the plus points in doing this
	struct controllerSticks
	{
		int16_t leftStick_Y;
		int16_t leftStick_X;
		int16_t rightStick_Y;
		int16_t rightStick_X;
	}playerOne;
	// Get all the current states of controller 1
	XInputGetState(0, &state);

	// Set both stick variables and attach them to the input
	playerOne.leftStick_Y = state.Gamepad.sThumbLY;
	playerOne.leftStick_X = state.Gamepad.sThumbLX;

	// Set the Deadzones for the stick
	const int16_t DEADZONE = 5000;

	// Deadzone Setting
	if (state.Gamepad.sThumbLY < DEADZONE && state.Gamepad.sThumbLY > -DEADZONE)
	{
		playerOne.leftStick_Y = 0;
	}

	if (state.Gamepad.sThumbLX < DEADZONE && state.Gamepad.sThumbLX > -DEADZONE)
	{
		playerOne.leftStick_X = 0;
	}

	// If the value is out of the dead zone then work!
	if (playerOne.leftStick_Y != 0)
	{
		player.y -= playerOne.leftStick_Y / 2000;
		vibrate(abs(playerOne.leftStick_Y) * 0.000004, abs(playerOne.leftStick_Y) * 0.000004);

		if (player.y >= 940)
		{
			player.y = 938;
		}

		if (player.y <= 110)
		{
			player.y = 112;
		}
	}

	// If the value is out of the dead zone then work!
	if (playerOne.leftStick_X != 0)
	{
		player.x += playerOne.leftStick_X / 2000;
		vibrate(abs(playerOne.leftStick_X) * 0.0000035, abs(playerOne.leftStick_X) * 0.0000035);

		if (player.x >= 1800)
		{
			player.x = 1798;
		}

		if (player.x <= 20)
		{
			player.x = 22;
		}

	}
}

//----------------------------------------------------------------------------------------------------//

void CheckControllerStatus(SDL_Rect &player, XINPUT_STATE &state, float &timer, gam::bullet &Bullet, uint8_t bulletAmount)
{
	// Button Checks Here
	if (timer > bulletAmount)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			Bullet.spawnBullet(player.x, player.y);
			timer = 0;
		}
	}
	// Set the movement off!
	movement(player, state);
}

//----------------------------------------------------------------------------------------------------//

