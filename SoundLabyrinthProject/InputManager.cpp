#include "InputManager.h"
#include <iostream>
#include <stdio.h>
#include "Singleton.h"

InputManager::InputManager()
{
	canType = false;
	isKeyPressed = false;
	boundBox.SetDimension2D(1.0f, 1.0f);
	isXclicked = false;
}

ButtonState InputManager::GetLeftButtonState()
{
	return m_leftButtonState;
}
ButtonState InputManager::GetMiddleButtonState()
{
	return m_middleButtonState;
}
ButtonState InputManager::GetRightButtonState()
{
	return m_rightButtonState;
}

const Uint8* InputManager::GetKeyStates()
{
	return keyStates;
}

bool InputManager::isXClicked()
{
	return isXclicked;
}

vec2 InputManager::getMousePos()
{
	return mousePos;
}

void InputManager::Update()
{
	boundBox.SetPosition2D(mousePos.x, mousePos.y);
	keyStates = SDL_GetKeyboardState(0);
	mouseMotion.y = 0;
	mouseMotion.x = 0;
	if (events.type == SDL_QUIT) { exit(0); }
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
			case SDL_KEYUP:
			{
				isKeyPressed = false;
				break;
			}

			case SDL_KEYDOWN:
			{
				if (events.key.keysym.sym == SDLK_BACKSPACE && !StringHolder.empty())
				{
					StringHolder.erase(StringHolder.end() - 1, StringHolder.end());
					StringHolder.resize(StringHolder.size());
				}
				if (!isKeyPressed && canType)
				{
					if (events.key.keysym.sym != SDLK_RETURN && events.key.keysym.sym != SDLK_BACKSPACE)
						symbols.push_back(events.key.keysym.sym);

					for (auto it = symbols.begin(); it != symbols.end(); it++)
					{
						StringHolder += (*it);
					}
					isKeyPressed = true;
					symbols.clear();
				}

				break;
			}

			case SDL_MOUSEMOTION:
			{
				mouseMotion.x = events.motion.xrel;
				mouseMotion.y = events.motion.yrel;

				cameraMotion.x = events.motion.xrel;
				cameraMotion.y = events.motion.yrel;

				mousePos.x = (float)events.motion.x;
				mousePos.y = (float)events.motion.y;
				break;
			}

			//a mouse button was clicked or released
			case SDL_MOUSEBUTTONUP: case SDL_MOUSEBUTTONDOWN:
			{
				//temporarily store button state for assigning below
				ButtonState state = ((events.button.state == SDL_PRESSED) ? DOWN : UP);

				mousePos.x = (float)events.motion.x;
				mousePos.y = (float)events.motion.y;

				//based on which of the three mouse buttons was pressed 
				//or released, assign flag to button's state variable
				switch (events.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					m_leftButtonState = state;
					break;
				}

				case SDL_BUTTON_MIDDLE:
				{
					m_middleButtonState = state;
					break;
				}

				case SDL_BUTTON_RIGHT:
				{
					m_rightButtonState = state;
					break;
				}

				break;

				}
				break;

			}
		}
	}
}
