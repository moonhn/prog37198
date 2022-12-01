#pragma once
#include "ScreenState.h"
#include <vector>
#include "ProgressBar.h"
using namespace std;

class LoadingScene : public ScreenState
{

private:
	ProgressBar* progressBar;
	SDL_Texture* progressBarTex;//load and store the progress bar background first
	SDL_Texture* bgSpriteTex;
	SpriteEx* bg;

public:
	LoadingScene() {}
	void Update(); // Method prototype.
	void Render();
	void Enter();
	void Exit();
	void Resume() {}
};