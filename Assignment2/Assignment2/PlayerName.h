#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class PlayerName
{
public:
	PlayerName();
	~PlayerName();
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Free();
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	TTF_Font* font = TTF_OpenFont("Font/LTYPE.TTF", 30);
};

