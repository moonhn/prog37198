#pragma once
#include "GameManager.h"
class Tracker
{
private:
	GameManager* m_pGameManager;
public:
	GameManager* GetGameManager() { return m_pGameManager; }
};

