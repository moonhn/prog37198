#include "LoadingScene.h"
#include <iostream>
#include "GameEngine.h"
#include "GameLevel1.h"
#include "MainMenuState.h"
#include "GameSetupState.h"
using namespace std;

Uint64 currentTime = SDL_GetPerformanceCounter();// re-start timer whenever entering pause menu for demonstration purpose
Uint64 lastRecordedTime = 0;
double deltaTime = 0;
double acculumatedTime = 0;

// Begin Loading Scene
void LoadingScene::Enter()
{
	bgSpriteTex = Game::Instance()->LoadTexture("Img/Levels/LoadingScene.png");

	SDL_Rect bgSrcRect;
	bgSrcRect.x = bgSrcRect.y = 0;
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	SDL_Rect bgDestRect;
	bgDestRect.x = bgDestRect.y = 0;
	SDL_GetWindowSize(Game::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);
		
	// Load texture of progress bar
	progressBarTex = Game::Instance()->LoadTexture("Img/progressBar.png");

	// Create new instance of progress bar where its background is loaded.
	progressBar = new ProgressBar(progressBarTex, 310, 400);
	progressBar->progressBarFill = new ProgressBar(progressBarTex, 310, 400);

	Game::Instance()->GetAM()->ToggleMusic();
	
}

void LoadingScene::Update()
{
	if (progressBar)
	{
		//std::cout << "progress bar is updating...\n";

		lastRecordedTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();

		deltaTime = (double)((currentTime - lastRecordedTime) * 100 / (double)SDL_GetPerformanceFrequency());

		//acculumatedTime += deltaTime;
		if (!progressBar->IsMaxedOut())
		{
			acculumatedTime++;

			progressBar->UpdateCurrentValue(acculumatedTime);

		}
		else progressBar->UpdateCurrentValue(0);

		progressBar->SetMaxValue(100);

		if (progressBar->IsMaxedOut())
		{
			Game::Instance()->GetFSM()->ChangeState(new GameSetupState());
			acculumatedTime = 0;
		}

		
	}

	/*
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	//close the pause menu popup
	if (m_vButtons[btn::resume]->Clicked())
	{
		Game::Instance()->GetFSM()->PopState();
	}
	//else if exit was clicked, we need to go back to main menu
	else if (m_vButtons[btn::exit]->Clicked())
	{
		Game::Instance()->GetFSM()->Clean(); // Clear all states, including GameState on bottom.
		//go back to main menu
		Game::Instance()->GetFSM()->ChangeState(new MainMenuState());
	}

	*/
	

}


void LoadingScene::Render()
{

	bg->Render();

	if (progressBar) progressBar->Render();
	
	ScreenState::Render();
}


void LoadingScene::Exit()
{

	cout << "Exiting Pause..." << endl;

	delete progressBar->progressBarFill;
	progressBar->progressBarFill = nullptr;

	delete progressBar;
	progressBar = nullptr;

	// resume music
	Game::Instance()->GetAM()->ToggleMusic();

}

