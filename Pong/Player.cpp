#include "Player.h"

Player::Player()
{
	FRect.w = 15; FRect.h = 150;
	FRect.x = 5; FRect.y = 540 - (FRect.h / 2);
	SetHitBox();
	Direction = NOTMOVING;
	Score = 0;
	Score_T = "0";
}

Player::~Player()
{
}

void Player::Update()
{
	if (Direction == UP) {
		int NewPos = FRect.y - PlayerSpeed;
		if (NewPos >= 0) {
			FRect.y = NewPos;
			SetHitBox();
		}
		else {
			FRect.y = 0;
			Direction = NOTMOVING;
			SetHitBox();
		}
	}
	if (Direction == DOWN) {
		int NewPos = FRect.y + PlayerSpeed;
		if (NewPos <= 1080 - FRect.h) {
			FRect.y = NewPos;
			SetHitBox();
		}
		else {
			FRect.y = 1080 - FRect.h;
			Direction = NOTMOVING;
			SetHitBox();
		}
	}
}

void Player::InputHandlingP1()
{
	switch (Event->key.keysym.sym) {
	case SDLK_w:
		Direction = UP;
		break;
	case SDLK_s:
		Direction = DOWN;
		break;
	default:
		break;
	}
	
}

void Player::InputHandlingP2()
{
	switch (Event->key.keysym.sym) {
	case SDLK_UP:
		Direction = UP;
		break;
	case SDLK_DOWN:
		Direction = DOWN;
		break;
	default:
		break;
	}

}
