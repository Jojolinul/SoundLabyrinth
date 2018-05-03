#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"
#include "AudioManager.h"

bool Game::Initialize()
{
	TheScreen::Instance()->Init("SoundLabyrinth", 1920, 1080, 3, 3, false, false);
	TheScreen::Instance()->ShowVendor();

	TheShader::Instance()->CreateProgram();														//Initialising the shader manager and opening/compiling the vertex / fragment shader
	TheShader::Instance()->CreateShaders();
	TheShader::Instance()->CompileShaders("Shaders/main.vert", VERT);
	TheShader::Instance()->CompileShaders("Shaders/main.frag", FRAG);
	TheShader::Instance()->AttachShaders();
	TheShader::Instance()->LinkProgram();

	TheTexture::Instance()->LoadFromFile("Assets/wall.jpg", "WallTexture");						//Loading all assets into the texture manager 
	TheTexture::Instance()->LoadFromFile("Assets/wireframe.jpg", "WireframeTexture");
	TheTexture::Instance()->LoadFromFile("Assets/menuBG.jpg", "menu");
	TheTexture::Instance()->LoadFromFile("Assets/end.jpg", "endBG");

	Audio::Instance()->Init();																	//Initialising the Audio manager and loading the sounds into the game
	Audio::Instance()->LoadSound("click.wav", false);

	States.push_back(new MenuState);															//Start the game on the menu screen

	deltaTime = 0;
	thisTime = 0;
	lastTime = 0;

	return true;
}

void Game::AddState(GameState* newState)
{
	States.push_back(newState);
}

void Game::ChangeState(GameState* newState)
{
	States.push_front(newState);
}

void Game::RemoveState()
{
	delete States.front();
	States.pop_front();
}

bool Game::Run()
{
	while (1)
	{
		while (States.front()->IsActive())
		{
			thisTime = SDL_GetTicks();
			TheScreen::Instance()->ClearScreen();
			Input::Instance()->Update();
			Audio::Instance()->Update();

			if (States.front()->IsAlive())
			{
				States.front()->Update(deltaTime);
				States.front()->Draw();
			}
			TheScreen::Instance()->SwapBuffer();
			deltaTime = (double)(SDL_GetTicks() - thisTime) / 1000;
		}

		if (!States.front()->IsActive())
		{
			RemoveState();
		}
		if (States.empty()) break;

	}

	return true;
}

void Game::ShutDown()
{
	TheScreen::Instance()->ShutDown();
}

Game::Game(const Game&)
{

}