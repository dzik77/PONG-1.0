#include "WindowManager.h"

WindowManager::WindowManager()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Initialized = false;
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL didn't initialize Video Component");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL didn't initialize Video Component","CRITIAL ERROR!",Window);
	}
	else SDL_Initialized = true;
	Window = nullptr;
	Renderer = nullptr;
	developer = false;
	Title = "";
	SCREEN_X = 0;
	SCREEN_Y = 0;
	SCREEN_WIDTH = 1000;
	SCREEM_HEIGHT = 1000;
	RENDERER_INDEX = 0;
	WINDOW_FLAGS = 0;
	RENDERER_FLAGS = 0;
}

WindowManager::WindowManager(bool dev)
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Initialized = false;
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL didn't initialize Video Component");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL didn't initialize Video Component", "CRITIAL ERROR!", Window);
	}
	else SDL_Initialized = true;
	Window = nullptr;
	Renderer = nullptr;
	developer = true;
	Title = "";
	SCREEN_X = 0;
	SCREEN_Y = 0;
	SCREEN_WIDTH = 1000;
	SCREEM_HEIGHT = 1000;
	RENDERER_INDEX = 0;
	WINDOW_FLAGS = 0;
	RENDERER_FLAGS = 0;
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(Window);
}

void WindowManager::InitWindow()
{
	const char* Title_C = Title.c_str();
	Window = SDL_CreateWindow(Title_C, SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEM_HEIGHT, WINDOW_FLAGS);
	return;
}

void WindowManager::InitWindow(const char* title, int SCREEN_X, int SCREEN_Y, int SCREEN_WIDTH, int SCREEN_HEIGHT, Uint32 FLAGS)
{
	Window = SDL_CreateWindow(title, SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEM_HEIGHT, FLAGS);
	return;
}

void WindowManager::InitRenderer()
{
	Renderer = SDL_CreateRenderer(Window, RENDERER_INDEX, RENDERER_FLAGS);
	return;
}

void WindowManager::InitRenderer(int RENDERER_INDEX, Uint32 RENDERER_FLAGS)
{
	Renderer = SDL_CreateRenderer(Window, RENDERER_INDEX, RENDERER_FLAGS);
	return;
}
