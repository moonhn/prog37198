#include "GameSetupState.h"
#include "GameEngine.h"
#include "GameLevel1.h"
#include "GameManager.h"
#include "LoadingScene.h"

SDL_Color color = { 0, 0, 0, 0xFF };

void GameSetupState::Enter()
{
	cout << "Entering GameSetup...\n";
	Game::Instance()->SetLeftMouse(false);

	m_vButtons.push_back(new Button("Img/play.png", { 0,0,400,100 }, { 312,200,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,400,400,100 }));
	m_vButtons.push_back(new Button("Img/exit.png", { 0,0,400,100 }, { 312,600,400,100 }));

	render = true;
	pName = "Name";
	
	inputText.LoadFromRenderedText(pName.c_str(), color);
	SDL_StartTextInput();
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
		Game::Instance()->GetFSM()->ChangeState(new LoadingScene());
	}

	else if (m_vButtons[btn::p2]->Clicked())
	{
		GameManager::Instance()->ChangePlayerSprite("Img/Players/EnemyKenSprite.png");
		GameManager::Instance()->ChangeEnemySprite("Img/Players/PlayerKenSprite2.png");
		Game::Instance()->GetFSM()->ChangeState(new LoadingScene());
	}
	else if (m_vButtons[btn::p3]->Clicked())
	{
		SDL_Delay(500);
		Game::Instance()->QuitGame();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		cout << "entering event..." << endl;
		if (e.type == SDL_KEYDOWN)
		{
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && pName.length() > 0)
			{
				//lop off character
				pName.pop_back();
				cout << "deleting a text..." << endl;
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(pName.c_str());

			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				pName = SDL_GetClipboardText();
			}
		}
		else if (e.type == SDL_TEXTINPUT)
		{
			//Not copy or pasting
			if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
			{
				//Append character
				pName += e.text.text;
				cout << "adding a char..." << endl;
			}
		}
	}
}

void GameSetupState::Render()
{

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(Game::Instance()->GetRenderer());
	for (int i = 0; i < (int)m_vButtons.size(); i++)
		m_vButtons[i]->Render();
	
	if (pName != "")
	{
		inputText.LoadFromRenderedText(pName.c_str(), color);
	}
	else
	{
		inputText.LoadFromRenderedText(" ", color);
	}

	inputText.Render((1082 - inputText.getWidth()) / 2, inputText.getHeight());

	ScreenState::Render();
}

void GameSetupState::Exit()
{
	cout << "Exiting GameSetup...\n";
	SDL_StopTextInput();
	for (int i = 0; i < (int)m_vButtons.size(); i++)
	{
		delete m_vButtons[i];
		m_vButtons[i] = nullptr;
	}

	m_vButtons.clear();
	m_vButtons.shrink_to_fit();

}