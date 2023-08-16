#include <SDL.h>
#include <string>
#include "Object.h"
#pragma once

#define UP 0
#define DOWN 1
#define NOTMOVING 2

class Player :
		public ObjectF
{
public:

	Player();
	~Player();
	void Update();
	void InputHandlingP1();
	void InputHandlingP2();

	SDL_Event* Event;
	int Score;
	std::string Score_T;
private:
	Uint8 Direction;
	const int PlayerSpeed = 7;
};

