#include "PlayerName.h"
#include "GameEngine.h"

PlayerName::PlayerName()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

PlayerName::~PlayerName()
{
	Free();
}

bool PlayerName::LoadFromRenderedText(std::string text, SDL_Color colour)
{
	Free();
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), colour);
	if (surface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), surface);
		if (mTexture == NULL)
		{
			cout << "unable to create texture from rendered text" << endl;
		}
		else
		{
			mWidth = surface->w;
			mHeight = surface->h;
		}

		SDL_FreeSurface(surface);
	}
	else
	{
		cout << "unable to render text sufrace" << endl;
	}
	return mTexture != NULL;
}

void PlayerName::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void PlayerName::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) 
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Game::Instance()->GetRenderer(), mTexture, clip, &renderQuad, angle, center, flip);
}

int PlayerName::getWidth()
{
	return mWidth;
}

int PlayerName::getHeight()
{
	return mHeight;
}