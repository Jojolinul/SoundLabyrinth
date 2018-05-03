#pragma once
#include <glm.hpp>
#include "AABB.h"
#include <SDL.h>
#include <vector>
#include "Singleton.h"

using namespace glm;
enum ButtonState { UP, DOWN };
class InputManager
{

public:
	friend class Singleton<InputManager>;

public:
	ButtonState GetLeftButtonState();
	ButtonState GetMiddleButtonState();
	ButtonState GetRightButtonState();
	vec2 getMousePos();
	AABB getBoundBox() { return boundBox; }

	void CanType(bool canT) { canType = canT; }
	void clearChat() { StringHolder.clear(); }
	std::string getSymbols() { return StringHolder; }

	void Update();
	bool isXClicked();
	const Uint8* GetKeyStates();
	vec2 mouseMotion;
	vec2 cameraMotion;

private:

	vec2 mousePos;
	bool isXclicked;
	const Uint8* keyStates;
	SDL_Event events;
	AABB boundBox;

private:
	ButtonState m_leftButtonState;
	ButtonState m_middleButtonState;
	ButtonState m_rightButtonState;

	bool isKeyPressed;
	bool canType;
	std::string StringHolder;
	std::vector<SDL_Keycode> symbols;

	InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);
};

typedef Singleton<InputManager> Input;