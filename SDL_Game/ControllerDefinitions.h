#pragma once
#include <Xinput.h>
#include <stdint.h>
#include <SDL.h>
#include <iostream>
#include "Bullet.h"


//#define XINPUT_GAMEPAD_DPAD_UP          0x00000001
//#define XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
//#define XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
//#define XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
//#define XINPUT_GAMEPAD_START            0x00000010
//#define XINPUT_GAMEPAD_BACK             0x0000002
//#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
//#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
//#define XINPUT_GAMEPAD_B                0x2000
//#define XINPUT_GAMEPAD_X                0x4000
//#define XINPUT_GAMEPAD_Y                0x8000

void CheckControllerStatus(SDL_Rect &player, XINPUT_STATE &state, float &timer, gam::bullet &Bullet, uint8_t bulletAmount);
void backButton();
bool controllerIsConnected(XINPUT_STATE &controller, XINPUT_VIBRATION &vibration);
SDL_Rect initRect(int16_t x, int16_t y);
