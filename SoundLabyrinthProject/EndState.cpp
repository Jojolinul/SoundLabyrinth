#include "stdafx.h"
#include "EndState.h"
#include "MenuState.h"


EndState::EndState() : bg("endBG")
{
	isAlive = true;
	isActive = true;

	SDL_PumpEvents();
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

bool EndState::Update(double deltaTime)
{
	keys = Input::Instance()->GetKeyStates();
	camera.camera.Update((float)deltaTime);
	bg.Update((float)deltaTime);

	if (keys[SDL_SCANCODE_SPACE])
	{
		isAlive = false;
		isActive = false;
		TheGame::Instance()->AddState(new MenuState);
		while (count < 3.0f)
		{
			if (deltaTime == 0)
			{
				count += 1 * 0.0000016f;
			}
			else
			{
				count += 1 * deltaTime;
			}
		}
	}

	return true;
}

bool EndState::Draw()
{
	TheScreen::Instance()->Set2DProjection();
	camera.camera.Draw2D();
	bg.Draw();

	return true;
}
