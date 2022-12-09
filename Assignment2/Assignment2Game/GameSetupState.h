#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <PlayerName.h>
using namespace std;

class GameSetupState : public ScreenState
{
private:
	vector<Button*> m_vButtons;
	enum btn { p1, p2, p3};
	string pName;
	bool render;
	PlayerName inputText;

public:
	GameSetupState() {}

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() {}
};

