#pragma once

#include "Singleton.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include <deque>
#include "PlayState.h"
#include "MenuState.h"
#include "GameState.h"
#include "AudioManager.h"
#include "EndState.h"
enum SHADERS { VERT, FRAG };

class Game
{

public:

	friend class Singleton<Game>;
	bool Initialize();
	bool Run();
	void ShutDown();
	void AddState(GameState* newState);
	void ChangeState(GameState* newState);
	double getDeltaTime() { return deltaTime; }
	std::deque<GameState*> States;

private:
	double deltaTime;
	double thisTime;
	double lastTime;
	void RemoveState();
	Game() {};
	Game(const Game&);
	Game& operator=(const Game&);
};

typedef Singleton<Game> TheGame;