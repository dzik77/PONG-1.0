#include <SDL.h>
#include <string>
#include <cstring>
#pragma once

constexpr bool DEVELOPER = true;

class WindowManager
{
public:

	//functions
	WindowManager();
	WindowManager(bool dev);
	~WindowManager();
	void InitWindow();
	void InitWindow(const char* title, int SCREEN_X, int SCREEN_Y, int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint32 FLAGS);
	void InitRenderer();
	void InitRenderer(int RENDERER_INDEX,Uint32 RENDERER_FLAGS);

	//developer functions
	inline SDL_Window* GetWindow() { return Window; }
	inline SDL_Renderer* GetRenderer() { return Renderer; }

	//variables
	std::string Title;
	int SCREEN_X,
		SCREEN_Y,
		SCREEN_WIDTH,
		SCREEM_HEIGHT,
		RENDERER_INDEX;
	Uint32 WINDOW_FLAGS;
	Uint32 RENDERER_FLAGS;
	bool SDL_Initialized;
	SDL_Window* Window;
	SDL_Renderer* Renderer;


private:

	//variables
	bool developer;

};

