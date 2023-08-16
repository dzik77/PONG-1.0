#include "Object.h"
#include <ctime>
#include <math.h>
#include <vector>
#include "CollisionBox.h"
#include "StringToChar.h"
#pragma once

#define PLAYER_1 -1
#define PLAYER_2 1

class Ball :
    public ObjectF
{
public:

    Ball();
    ~Ball();
    void InitRenderer(SDL_Renderer* Renderer);
    void RenderBall();
    void UpdateBall();
    void AddCollision(CollisionBox* NewCollisionBox);
    void CollisionManagment();
    int BallFallOff();
    void BallStop();
    void RandomShootOut(int8_t Player);

    double* DeltaTime;

private:

    int Collisions = 1;

    void RecalculateBallSpeed();

    SDL_Renderer* Renderer;

    const int BallCircumference = 20;
    int BallSpeed;
    double
        Speed_X,
        Speed_Y,
        Speed_X_Additional,
        Speed_Y_Additional,
        BallSpeed_X,
        BallSpeed_Y,
        BallSpeed_X_Additional,
        BallSpeed_Y_Additional;


    //Collisions
    std::vector <CollisionBox*> CollisionBoxes;
    int CollisionBufferX;
    int CollisionBufferY;


};

