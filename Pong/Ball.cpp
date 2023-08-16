#include "Ball.h"

Ball::Ball()
{
	srand(time(NULL));
	FRect.w = FRect.h = 20; FRect.x = 960; FRect.y = 540;
	FRect.x -= 10; FRect.y -= 10;
}

Ball::~Ball()
{
}

void Ball::InitRenderer(SDL_Renderer* Renderer)
{
	this->Renderer = Renderer;
	if (!Renderer) SDL_Log("Renderer isn\'t initialized");
	return;
}

void Ball::RenderBall()
{
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderFillRectF(Renderer, &FRect);
}

void Ball::UpdateBall()
{

	// axis-x
	CollisionBufferX = FRect.x;

	FRect.x += BallSpeed_X;

	BallSpeed_X_Additional += Speed_X_Additional;
	FRect.x += (int)BallSpeed_X_Additional;
	BallSpeed_X_Additional -= (int)BallSpeed_X_Additional;

	// y-axis
	CollisionBufferY = FRect.y;

	FRect.y += BallSpeed_Y;

	BallSpeed_Y_Additional += Speed_Y_Additional;
	FRect.y += (int)BallSpeed_Y_Additional;
	BallSpeed_Y_Additional -= (int)BallSpeed_Y_Additional;
}

void Ball::AddCollision(CollisionBox* NewCollisionBox)
{
	CollisionBoxes.push_back(NewCollisionBox);
}

void Ball::CollisionManagment()
{
	/*
		Y1
	     __
	X1	\_\  X2
	     Y2
		 

	*/


	for (int i = 0; i < CollisionBoxes.size(); i++) {
	
		// axis-y Collision
		if (FRect.y + BallCircumference >= CollisionBoxes[i]->WallY1 && CollisionBufferY + BallCircumference <= CollisionBoxes[i]->WallY1 && BallSpeed_Y > 0) {
			// Wzór na ilosc klatek: (CollisionBoxes[i].WallY1 - FRect.y) / -(Speed_Y * BallSpeed)
			//SDL_Log("Logging collision down");
			int XCollisionPoint = FRect.x + (((CollisionBoxes[i]->WallY1 - FRect.y) / -(BallSpeed_Y)) * -BallSpeed_X);
			if (XCollisionPoint + BallCircumference >= CollisionBoxes[i]->WallX1 && XCollisionPoint <= CollisionBoxes[i]->WallX2) {
				CollisionBufferY = FRect.y;
				int Ydif = CollisionBoxes[i]->WallY1 - FRect.y;
				FRect.y = CollisionBoxes[i]->WallY1 + Ydif - BallCircumference;
				Speed_Y *= -1;
				BallSpeed_Y *= -1;
				BallSpeed_Y_Additional *= -1;
				Speed_Y_Additional *= -1;
				Collisions++;
				


				/*std::string YS = std::to_string(Speed_Y);
				char* YSC = &YS[0];
				SDL_Log(YSC);
				std::string XS = std::to_string(Speed_X);
				char* XSC = &XS[0];
				SDL_Log(XSC);*/
				double YSpeedRebounce;
				double minusY = -1 - Speed_Y;
				double plusY = 1 - Speed_Y;
				if (minusY < -0.15 && plusY > 0.15) {
					YSpeedRebounce = (rand() % 3001 - 1500) / 10'000.0;
				}
				else {
						plusY *= 1000;
						plusY++;
						minusY *= 1000;
						YSpeedRebounce = (rand() % (int)plusY - minusY) / 10'000.0;
				}
				Speed_Y += YSpeedRebounce;
				Speed_X = (1 - abs(Speed_Y)) * (Speed_X > 0 ? 1 : -1);
				RecalculateBallSpeed();
				

			}
		}
		
		if (FRect.y <= CollisionBoxes[i]->WallY2 && CollisionBufferY >= CollisionBoxes[i]->WallY2 && BallSpeed_Y < 0) {
			//SDL_Log("Logging collision top");
			int XCollisionPoint = FRect.x + (((CollisionBoxes[i]->WallY2 - FRect.y) / BallSpeed_Y) * -BallSpeed_X);
			if (XCollisionPoint + BallCircumference >= CollisionBoxes[i]->WallX1 && XCollisionPoint <= CollisionBoxes[i]->WallX2) {
				CollisionBufferY = FRect.y;
				int Ydif = CollisionBoxes[i]->WallY2 - FRect.y;
				FRect.y = CollisionBoxes[i]->WallY2 + Ydif + BallCircumference;
				Speed_Y *= -1;
				BallSpeed_Y *= -1;
				BallSpeed_Y_Additional *= -1;
				Speed_Y_Additional *= -1;
				Collisions++;

				double YSpeedRebounce;
				double minusY = -1 - Speed_Y;
				double plusY = 1 - Speed_Y;
				if (minusY < -0.15 && plusY > 0.15) {
					YSpeedRebounce = (rand() % 3001 - 1500) / 10'000.0;
				}
				else {
					plusY *= 1000;
					plusY++;
					minusY *= 1000;
					YSpeedRebounce = (rand() % (int)plusY - minusY) / 10'000.0;
				}
				Speed_Y += YSpeedRebounce;
				Speed_X = (1 - abs(Speed_Y)) * (Speed_X > 0 ? 1 : -1);
				RecalculateBallSpeed();
			}
		}
		
		// axis-x Collision
		if (FRect.x + BallCircumference >= CollisionBoxes[i]->WallX1 && CollisionBufferX + BallCircumference <= CollisionBoxes[i]->WallX1 && BallSpeed_X > 0) {
			//SDL_Log("Logging collision right");
			// Wzór na ilosc klatek: (CollisionBoxes[i].WallY1 - FRect.y) / -(Speed_Y * BallSpeed)
			int YCollisionPoint = FRect.y + (((CollisionBoxes[i]->WallX1 - FRect.x) / -(BallSpeed_X)) * -BallSpeed_Y);
			if (YCollisionPoint + BallCircumference >= CollisionBoxes[i]->WallY1 && YCollisionPoint<= CollisionBoxes[i]->WallY2) {
			 	CollisionBufferX = FRect.x;
				int Xdif = CollisionBoxes[i]->WallX1 - FRect.x;
				FRect.x = CollisionBoxes[i]->WallX1 + Xdif - BallCircumference;
				Speed_X *= -1;
				BallSpeed_X *= -1;
				BallSpeed_X_Additional *= -1;
				Speed_X_Additional *= -1;
				Collisions++;

				double YSpeedRebounce;
				double minusY = -1 - Speed_Y;
				double plusY = 1 - Speed_Y;
				if (minusY < -0.15 && plusY > 0.15) {
					YSpeedRebounce = (rand() % 3001 - 1500) / 10'000.0;
				}
				else {
					plusY *= 1000;
					plusY++;
					minusY *= 1000;
					YSpeedRebounce = (rand() % (int)plusY - minusY) / 10'000.0;
				}
				Speed_Y += YSpeedRebounce;
				Speed_X = (1 - abs(Speed_Y)) * (Speed_X > 0 ? 1 : -1);
				RecalculateBallSpeed();
			}
		}

		if (FRect.x <= CollisionBoxes[i]->WallX2 && CollisionBufferX >= CollisionBoxes[i]->WallX2 && BallSpeed_X < 0) {
			//SDL_Log("Logging collision left");
			int YCollisionPoint = FRect.y + (((CollisionBoxes[i]->WallX2 - FRect.x) / BallSpeed_X) * -BallSpeed_Y);
			if (YCollisionPoint + BallCircumference >= CollisionBoxes[i]->WallY1 && YCollisionPoint <= CollisionBoxes[i]->WallY2) {
				CollisionBufferX = FRect.x;
				int Xdif = CollisionBoxes[i]->WallX2 - FRect.x;
				FRect.x = CollisionBoxes[i]->WallX2 + Xdif;
				Speed_X *= -1;
				BallSpeed_X *= -1;
				BallSpeed_X_Additional *= -1;
				Speed_X_Additional *= -1;
				Collisions++;

				double YSpeedRebounce;
				double minusY = -1 - Speed_Y;
				double plusY = 1 - Speed_Y;
				if (minusY < -0.15 && plusY > 0.15) {
					YSpeedRebounce = (rand() % 3001 - 1500) / 10'000.0;
				}
				else {
					plusY *= 1000;
					plusY++;
					minusY *= 1000;
					YSpeedRebounce = (rand() % (int)plusY - minusY) / 10'000.0;
				}
				Speed_Y += YSpeedRebounce;
				Speed_X = (1 - abs(Speed_Y)) * (Speed_X > 0 ? 1 : -1);
				RecalculateBallSpeed();
			}
		}
		
		if (Collisions % 3 == 0) {
			BallSpeed++;
			RecalculateBallSpeed();
			Collisions++;
		}
		 
		
	}
}

void Ball::RecalculateBallSpeed()
{
	BallSpeed_X_Additional = 0;
	BallSpeed_Y_Additional = 0;
	BallSpeed_X = BallSpeed * Speed_X;
	BallSpeed_Y = BallSpeed * Speed_Y;
	Speed_X_Additional = (BallSpeed_X - (int)BallSpeed_X);
	Speed_Y_Additional = (BallSpeed_Y - (int)BallSpeed_Y);
}

int Ball::BallFallOff()
{
	if (FRect.x <= 0) {
		return PLAYER_1;
		Collisions = 1;
		BallSpeed = 4;
	}
	if (FRect.x >= 1920) {
		return PLAYER_2;
		Collisions = 1;
		BallSpeed = 4;
	}
	return 0;
}

void Ball::BallStop()
{
	FRect.x = 100; FRect.y = -20;
	Speed_X = 0;
	Speed_Y = 0;
	Speed_X_Additional = 0;
	Speed_Y_Additional = 0;
	BallSpeed_X = 0;
	BallSpeed_Y = 0;
	BallSpeed_X_Additional = 0;
	BallSpeed_Y_Additional = 0;
}

void Ball::RandomShootOut(int8_t Player)
{

	if (Player == PLAYER_1) FRect.x = 950 - BallCircumference;
	else if (Player == PLAYER_2) FRect.x = 970;
	FRect.y = 540;
	Speed_X = 0;
	Speed_Y = 0;
	Speed_X_Additional = 0;
	Speed_Y_Additional = 0;
	BallSpeed_X = 0;
	BallSpeed_Y = 0;
	BallSpeed_X_Additional = 0;
	BallSpeed_Y_Additional = 0;
	BallSpeed = 4;
    Speed_Y = (rand() % 15001 + (-7500)) / 10000.0; // value between -0.7500 to 0.7500
	Speed_X = (1 - abs(Speed_Y)) * Player; // value between 0.25 to 1
	/*std::string sy = std::to_string(Speed_Y);
	char* syc = &sy[0];
	SDL_Log(syc);
	std::string sx = std::to_string(Speed_X);
	char* sxc = &sx[0];
	SDL_Log(sxc);
	*/
	BallSpeed_X = BallSpeed * Speed_X; // actual ball speedX
	BallSpeed_Y = BallSpeed * Speed_Y; // actual ball speedY

	Speed_X_Additional = (BallSpeed_X - (int)BallSpeed_X);

	Speed_Y_Additional = (BallSpeed_Y - (int)BallSpeed_Y);

	/*
	std::string BSY_S = std::to_string(BSY);
	char* BSY_SC = &BSY_S[0];
	SDL_Log(BSY_SC);
	std::string BSX_S = std::to_string(BSX);
	char* BSX_SC = &BSX_S[0];
	SDL_Log(BSX_SC);
	*/
	//BallSpeed_X = (int)BallSpeed_X;
	//BallSpeed_Y = (int)BallSpeed_Y;
}
