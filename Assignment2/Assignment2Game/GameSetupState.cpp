#include "GameSetupState.h"
#include "GameEngine.h"
#include "GameLevel1.h"
#include "GameManager.h"
#include "LoadingScene.h"

void GameSetupState::Enter()
{
	cout << "Entering GameSetup...\n";
	Game::Instance()->SetLeftMouse(false);

	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,200,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,400,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,600,400,100 }));
}

void GameSetupState::Update()
{

	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Update();

	if (m_vButtons[btn::p1]->Clicked())
	{
		//we need to switch to gamestate ... 
		GameManager::Instance()->ChangePlayerSprite("Img/Players/PlayerKenSprite2.png");
		GameManager::Instance()->ChangeEnemySprite("Img/Players/EnemyKenSprite.png");
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}

	else if (m_vButtons[btn::p2]->Clicked())
	{
		GameManager::Instance()->ChangePlayerSprite("Img/Players/EnemyKenSprite.png");
		GameManager::Instance()->ChangeEnemySprite("Img/Players/PlayerKenSprite2.png");
		Game::Instance()->GetFSM()->ChangeState(new GameLevel1());
	}
	else if (m_vButtons[btn::p3]->Clicked())
	{
		SDL_Delay(500);
		Game::Instance()->QuitGame();
	}

}

void GameSetupState::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();

	ScreenState::Render();
}

void GameSetupState::Exit()
{
	cout << "Exiting GameSetup...\n";

	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}
	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}