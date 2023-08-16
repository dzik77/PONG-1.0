#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cstring>
#include <vector>
#pragma once

#define Arial 0
#define PongScore 1

class MessageManager
{
public:

	//functions
	MessageManager();
	~MessageManager();
	void InitWindowAndRenderer(SDL_Window* Window, SDL_Renderer* Renderer);
	SDL_Texture* LoadMessage(std::string Text,int Font, int FontSize);

	bool SDL_Initialized;

private:

	void LoadFonts(int Font,int Size);

	//fonts
	std::vector <TTF_Font*> Fonts{nullptr,nullptr};

	//colors
	SDL_Color White;

	//renderer
	SDL_Renderer* Renderer;
	SDL_Window* Window;

};

