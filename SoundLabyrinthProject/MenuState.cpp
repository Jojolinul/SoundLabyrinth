#include "MenuState.h"
#include "Tool.h"

MenuState::MenuState() : bg("menu")
{
	isAlive = true;
	isActive = true;

	SDL_PumpEvents();
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

bool MenuState::Update(double deltaTime)
{
	keys = Input::Instance()->GetKeyStates();
	camera.camera.Update((float)deltaTime);
	bg.Update((float)deltaTime);
	pressEnter = false;

	if (keys[SDL_SCANCODE_RETURN])
	{
		isAlive = false;
		isActive = false;
		TheGame::Instance()->AddState(new PlayState);
		pressEnter = true;
	}

	return true;
}

bool MenuState::Draw()
{
	TheScreen::Instance()->Set2DProjection();
	camera.camera.Draw2D();
	if (!pressEnter)	bg.Draw();

	return true;
}
