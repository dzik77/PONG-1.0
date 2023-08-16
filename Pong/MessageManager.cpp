#include "MessageManager.h"

MessageManager::MessageManager()
{
	Window = nullptr;
	Renderer = nullptr;
	if (TTF_Init()) {
		SDL_Initialized = false;
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL didn't initialize TTF Component");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL didn't initialize TTF Component", "CRITIAL ERROR!", Window);
	}
	else SDL_Initialized = true;
	White.r = 255; White.g = 255; White.b = 255; White.a = 255;
}

MessageManager::~MessageManager()
{
}

void MessageManager::LoadFonts(int Font, int Size)
{
	if(Font == Arial)
		Fonts[Font] = TTF_OpenFont("Fonts\\Arial.ttf", Size);
	else if(Font == PongScore)
		Fonts[Font] = TTF_OpenFont("Fonts\\pong-score.ttf", Size);
}

void MessageManager::InitWindowAndRenderer(SDL_Window* Window, SDL_Renderer* Renderer)
{
	this->Window = Window;
	this->Renderer = Renderer;
	if (!Window || !Renderer) SDL_Log("Window or renderer wasnt loaded");
}

SDL_Texture* MessageManager::LoadMessage(std::string Text, int Font,int FontSize)
{
	LoadFonts(Font,FontSize);
	const char* Text_C = Text.c_str();
	SDL_Surface* MessageSurface = TTF_RenderText_Solid(Fonts[Font], Text_C, White);
	if (!MessageSurface) SDL_Log("Surface wasnt created");
	SDL_Texture* MessageTexture = SDL_CreateTextureFromSurface(Renderer, MessageSurface);
	if (!MessageTexture) SDL_Log(SDL_GetError());
	SDL_FreeSurface(MessageSurface);
	return MessageTexture;
}
