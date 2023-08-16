#include "WindowManager.h"
#include "CollisionBox.h"
#pragma once

class ObjectT
{
public:

	//functions
	ObjectT();
	~ObjectT();

	//variables
	SDL_Rect Dst;
	SDL_Rect Src;

	SDL_Texture* Texture;


};

class ObjectF
{
public:

	//functions
	ObjectF();
	~ObjectF();
	void SetHitBox();

	//variables
	SDL_FRect FRect;
	CollisionBox Box;


};
