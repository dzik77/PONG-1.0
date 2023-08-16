#include "WindowManager.h"
#include "MessageManager.h"
#include "Object.h"
#include "Ball.h"
#include "Player.h"

/*
    
*/

WindowManager Window(DEVELOPER);
MessageManager Message;
bool Running;
SDL_Event Event;
int GameState;

//FPS Initialization:
//? Note that the game doesn't support diffrent framerates! 
constexpr int FPS = 120;
constexpr float Delay = 1000.f / FPS;
Uint64 TicksStart;
Uint64 TicksEnd;
float FrameTime;
int FrameFPS = FPS;
double DeltaTime = 1.0;

Player Player1;
Player Player2;

Ball ball;

ObjectF BottomWall;
ObjectF TopWall;
ObjectF MiddleWall;
ObjectF RightWall;
ObjectF LeftWall;

ObjectT Player1ScoreText;
ObjectT Player2ScoreText;
ObjectT FrameFPSText;
ObjectT PongText;
ObjectT EnterText;

void InputHandling();
void RenderMiddleWall();
void Menu();

int main(int argc, char *argv[]) {

	//Timer Initialization:
	if (SDL_Init(SDL_INIT_TIMER)) {
		SDL_Log("ERROR 1");
		system("pause");
		return 1;
	}	

	//Window Initialization:
	if (!Window.SDL_Initialized) {
		SDL_Log("ERROR 2");
		system("pause");
		return 1;
	}
	Window.SCREEN_WIDTH = 1920; Window.SCREEM_HEIGHT = 1080;
	Window.SCREEN_X = SDL_WINDOWPOS_CENTERED; Window.SCREEN_Y = SDL_WINDOWPOS_CENTERED;
	Window.Title = "PONG";
	Window.WINDOW_FLAGS = NULL;
	Window.InitWindow();

	//Renderer Initialization:
	Window.RENDERER_INDEX = -1;
	Window.RENDERER_FLAGS = NULL;
	Window.InitRenderer();

	//Message Initialization:
	if (!Message.SDL_Initialized) {
		SDL_Log("ERROR 3");
		system("pause");
		return 1;
	}
	Message.InitWindowAndRenderer(Window.Window, Window.Renderer);

	//Loop Initialization:
	Running = Window.SDL_Initialized;
	Running = Message.SDL_Initialized;

	//Objects Initialization:
	ball.InitRenderer(Window.Renderer);
	ball.DeltaTime = &DeltaTime;
	ball.RandomShootOut((rand() % 2 ? PLAYER_1 : PLAYER_2));

	Player1.Event = &Event;
	Player1.FRect.x = 70;
	Player1.SetHitBox();
	ball.AddCollision(&Player1.Box);

	Player2.Event = &Event;
	Player2.FRect.x = 1850 - Player2.FRect.w;
	Player2.SetHitBox();
	ball.AddCollision(&Player2.Box);

	BottomWall.FRect.x = 0; BottomWall.FRect.y = 1080; BottomWall.FRect.w = 1920; BottomWall.FRect.h = 0;
	BottomWall.SetHitBox();
	ball.AddCollision(&BottomWall.Box);

	TopWall.FRect.x = 0; TopWall.FRect.y = 0; TopWall.FRect.w = 1920; TopWall.FRect.h = 0;
	TopWall.SetHitBox();
	ball.AddCollision(&TopWall.Box);

	MiddleWall.FRect.w = 20; MiddleWall.FRect.h = 50; MiddleWall.FRect.y = 0; MiddleWall.FRect.x = 960 - (MiddleWall.FRect.w / 2);

	Player1ScoreText.Dst.w = 150; Player1ScoreText.Dst.h = 150; Player1ScoreText.Dst.x = 770; Player1ScoreText.Dst.y = 40;
	Player1ScoreText.Texture = Message.LoadMessage(Player1.Score_T, PongScore,50);

	Player2ScoreText.Dst.w = 150; Player2ScoreText.Dst.h = 150; Player2ScoreText.Dst.x = 1220 - Player2ScoreText.Dst.w; Player2ScoreText.Dst.y = 40;
	Player2ScoreText.Texture = Message.LoadMessage(Player2.Score_T, PongScore,50);

	FrameFPSText.Dst.w = 100; FrameFPSText.Dst.h = 50; FrameFPSText.Dst.x = 25;  FrameFPSText.Dst.y = 25;

	PongText.Dst.w = 1300; PongText.Dst.h = 700; PongText.Dst.x = 100; PongText.Dst.y = 50;
	PongText.Texture = Message.LoadMessage("PONG", Arial, 1500);

	EnterText.Dst.w = 1000; EnterText.Dst.h = 150; EnterText.Dst.x = 130; EnterText.Dst.y = 600;
	EnterText.Texture = Message.LoadMessage("Press Enter to continue...", Arial, 500);

	/*
	LeftWall.FRect.x = 0; LeftWall.FRect.y = 20; LeftWall.FRect.w = 20; LeftWall.FRect.h = 1040;
	LeftWall.SetHitBox();
	ball.AddCollision(&LeftWall.Box);

	RightWall.FRect.x = 1900; RightWall.FRect.y = 20; RightWall.FRect.w = 20; RightWall.FRect.h = 1040;
	RightWall.SetHitBox();
	ball.AddCollision(&RightWall.Box);
	*/
	Menu();
	while (Running) {
		//Starting Time managment
		TicksStart = SDL_GetPerformanceCounter();

		//Input
		InputHandling();

		//Updates
		ball.UpdateBall();
		Player1.Update();
		Player2.Update();
		ball.CollisionManagment();
		GameState = ball.BallFallOff();
		if (GameState) {
			if (GameState == PLAYER_2) {
				Player1.Score++;
				Player1.Score_T = std::to_string(Player1.Score);
				Player1ScoreText.Texture = Message.LoadMessage(Player1.Score_T, PongScore, 50);
				ball.BallStop();
				if (Player1.Score == 10) Running = false;
			}
			if (GameState == PLAYER_1) {
				Player2.Score++;
				Player2.Score_T = std::to_string(Player2.Score);
				Player2ScoreText.Texture = Message.LoadMessage(Player2.Score_T, PongScore, 50);
				ball.BallStop();
				if (Player2.Score == 10) Running = false;
			}
			ball.RandomShootOut((rand() % 2 ? PLAYER_1 : PLAYER_2));
		}

		//Rendering Objects
		SDL_RenderClear(Window.Renderer);
		ball.RenderBall();
		SDL_SetRenderDrawColor(Window.Renderer, 255, 255, 255, 255);
		SDL_RenderFillRectF(Window.Renderer, &Player1.FRect);
		SDL_RenderFillRectF(Window.Renderer, &Player2.FRect);
		RenderMiddleWall();
		SDL_RenderCopy(Window.Renderer, Player1ScoreText.Texture, NULL, &Player1ScoreText.Dst);
		SDL_RenderCopy(Window.Renderer, Player2ScoreText.Texture, NULL, &Player2ScoreText.Dst);
		//SDL_RenderFillRectF(Window.Renderer, &RightWall.FRect);
		//SDL_RenderFillRectF(Window.Renderer, &LeftWall.FRect);
		SDL_SetRenderDrawColor(Window.Renderer, 0, 0, 0, 0);

		SDL_RenderPresent(Window.Renderer);

		//Time managment
		TicksEnd = SDL_GetPerformanceCounter();
		FrameTime = (TicksEnd - TicksStart) / (float)SDL_GetPerformanceFrequency() * 1000.f;
		
		if (FrameTime < Delay) {
			SDL_Delay(Delay - FrameTime);
			FrameTime = Delay;
		}
		
		FrameFPS = 1000.f / FrameTime;

		//Updating Texts
		//FrameFPSText.Texture = Message.LoadMessage(std::to_string(FrameFPS), 100);

		//Rendering Texts
		//SDL_RenderCopy(Window.Renderer, FrameFPSText.Texture, NULL, &FrameFPSText.Dst);

		//Presenting Window
		//SDL_RenderPresent(Window.Renderer);
	}

	Window.~WindowManager();
	Message.~MessageManager();
	SDL_Quit();

	return 0;
}

void InputHandling() {
	SDL_PollEvent(&Event);
	switch (Event.type) {
	case SDL_QUIT:
		Running = false;
		break;
	default:
		break;
	}
	switch (Event.key.keysym.sym) {
	case SDLK_ESCAPE:
		Running = false;
		break;
	case SDLK_r:
		ball.RandomShootOut(PLAYER_2);
		break;
	case SDLK_e:
		ball.RandomShootOut(PLAYER_1);
		break;
	default:
		break;
	}
	Player1.InputHandlingP1();
	Player2.InputHandlingP2();
}

void RenderMiddleWall() {
	while (MiddleWall.FRect.y <= 1080) {
		SDL_RenderFillRectF(Window.Renderer, &MiddleWall.FRect);
		MiddleWall.FRect.y += MiddleWall.FRect.h + 20;
	}
	MiddleWall.FRect.y = 0;
}

void Menu() {
	bool MenuRunning = true;
	while (MenuRunning) {
		SDL_PollEvent(&Event);
		switch (Event.type) {
		case SDL_QUIT:
			MenuRunning = false;
			Running = false;
			break;
		default:
			break;
		}
		switch (Event.key.keysym.sym) {
		case SDLK_ESCAPE:
			MenuRunning = false;
			Running = false;
			break;
		case SDLK_RETURN:
			MenuRunning = false;
			break;
		default:
			break;
		}
		SDL_RenderClear(Window.Renderer);
		SDL_RenderCopy(Window.Renderer,PongText.Texture,NULL,&PongText.Dst );
		SDL_RenderCopy(Window.Renderer, EnterText.Texture, NULL, &EnterText.Dst);
		SDL_RenderPresent(Window.Renderer);
		
	}

}