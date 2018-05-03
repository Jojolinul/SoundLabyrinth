#pragma once

class GameState
{
public:
	GameState() {};

	virtual bool Update(double deltaTime) = 0;
	virtual bool Draw() = 0;

	bool& IsAlive() { return isAlive; }
	bool& IsActive() { return isActive; }

	virtual ~GameState() = 0 {};

protected:

	bool isAlive = true;
	bool isActive = true;
};

