#include "PlayState.h"
#include "Game.h"
#include "Tool.h"
#include "EndState.h"
#include "InputManager.h"

PlayState::PlayState() : playerLight(0)
{
	isAlive = true;
	isActive = true;

	AttenuationID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "AttenuationDistance"); // Default value 0.5f
	fogID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "FogDistance");					// Default value 5.0f

	playerLight.setAmbient(vec3(0.7f));												//Setting up the light for the player
	playerLight.setDiffuse(vec3(1.0f, 0.3f, 0.2f));
	playerLight.setSpecular(vec3(0.0f, 1.0f, 0.0f));

	labyrinthData = readTFile("Labyrinth/Labyrinth.txt");							//Using the Tools class, loading in a text file line by line and storing
																					//it into a vector of type string

	labyrinthWall_Object.LoadModel("Assets/wall.obj", finalVertices, finalNormals,			//Loading the generic Wall 3D model once (all the parameters are passed by reference
		finalUVs, indices);

	labyrinthWall_Object.LoadModel("Assets/chair.obj", chairFinalVertices, chairFinalNormals,			//Loading the generic Wall 3D model once (all the parameters are passed by reference
		chairFinalUVs, chairIndices);

	CreateLabyrinth();																//Creating the labyrinth based on the data we read from the text file

	while (fogAmount < 5.0f)														//This is a "mini" gamestate in itself, this is the intro at the start of the game
	{
		TheScreen::Instance()->ClearScreen();

		if (TheGame::Instance()->getDeltaTime() == 0) {
			fogAmount += 3.0f * 0.0016f;
		}
		else {
			fogAmount += 3.0f * (float)TheGame::Instance()->getDeltaTime();
		}

		glUniform1f(AttenuationID, attenuationAmount);
		glUniform1f(fogID, fogAmount);
		player.Update(0.0f);
		playerLight.setgetPosition() = player.camera.getPosition();
		playerLight.Update(0.0f);

		TheScreen::Instance()->Set3DProjection();
		player.camera.Draw();
		playerLight.Draw(true);
		for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); it++)
		{
			float distanceToWall = glm::length((*it)->getPos() - player.camera.getPosition());
			if (distanceToWall < 50.0f)
			{
				(*it)->Draw();
			}
		}
		labyrinthFloor->Draw();

		TheScreen::Instance()->SwapBuffer();
	}

	fogAmount = 5.0f;
	SDL_PumpEvents();																//After you set relative mouse mode the mouse gets stuck as it was pressing the left key,
	SDL_SetRelativeMouseMode(SDL_TRUE);												//PumpEvents fixes that
}

bool PlayState::Update(double deltaTime)
{
	keys = Input::Instance()->GetKeyStates();										//Read keyboard state from the Input manager
																					//Update all our GameObjects
	player.Update(deltaTime);
	playerLight.setgetPosition() = player.camera.getPosition();
	playerLight.Update(deltaTime);

	if (player.getBoundBox().IsColliding(endChair->getBoundBox()))
	{
		isAlive = false;
		isActive = false;
		TheGame::Instance()->AddState(new EndState);
	}

	for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	if (keys[SDL_SCANCODE_ESCAPE])													//Check for keyboard input for certain things
	{
		isActive = false;
		isAlive = false;
	}
	if (keys[SDL_SCANCODE_KP_PLUS])
	{
		fogAmount += 10.0f * deltaTime;
	}

	if (keys[SDL_SCANCODE_KP_MINUS])
	{
		fogAmount -= 10.0f * deltaTime;
	}

	if (Input::Instance()->GetMiddleButtonState())	player.camera.setFreecam(true);	//Hold the middle-mouse button (scroll button) to enable the freecam
	else player.camera.setFreecam(false);
	return true;
}

bool PlayState::Draw()
{
	glUniform1f(AttenuationID, attenuationAmount);									//Sending to the shader the amount of attenuation and fog
	glUniform1f(fogID, fogAmount);													//(can be changed with keys while in-game) ( '+' and '-')

	TheScreen::Instance()->Set3DProjection();										//Setting up the screen for 3D Projection

	player.camera.Draw();															//Since the player class has the camera attached we call the draw
	playerLight.Draw(true);															//function from the player itself (same for the update)
	endChair->Draw();

	for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); it++)
	{
		float distanceToWall = glm::length((*it)->getPos() - player.camera.getPosition());
		if (distanceToWall < 30.0f)
		{
			(*it)->Draw();
		}
		else if (distanceToWall > 30.0f && (*it)->IsShaking())
		{
			(*it)->Draw();
		}
	}

	labyrinthFloor->Draw();
	return true;
}


void PlayState::CreateLabyrinth()													//Loop through all the labyrinth data from the text file and place a wall / player where it's
{																					//supposed to go
	int wallIDCounter = 0;
	float lastX, lastZ;

	if (labyrinthData.empty()) cout << ("Labyrinth Text File Not Initialized / Non Existent") << endl;
	else
	{
		for (int zValue = 0; zValue < labyrinthData.size(); zValue++)
		{
			for (int xValue = 0; xValue < labyrinthData[zValue].size(); xValue++)
			{
				if (labyrinthData[zValue][xValue] == 'a')
				{
					Wall* tempWall = new Wall(wallIDCounter, vec3(xValue * 5.0f, 1.0f, zValue * 5.0f), finalVertices, finalNormals, finalUVs, indices);
					labyrinthWalls.push_back(tempWall);
					wallIDCounter++;
					lastX = xValue * 5.0f;
					lastZ = zValue * 5.0f;
				}

				if (labyrinthData[zValue][xValue] == 'x')
				{
					player.camera.setInitialPos(vec3(xValue * 5.0f, 1.0f, zValue * 5.0f));
					player.setPos(vec3(xValue * 5.0f, 1.0f, zValue * 5.0f));

				}

				if (labyrinthData[zValue][xValue] == 'e')
				{
					endChair = new Chair(0, vec3(xValue * 5.0f, -1.5f, zValue * 5.0f), chairFinalVertices, chairFinalNormals, chairFinalUVs, chairIndices);
					player.SetEndPosition(vec3(xValue * 5.0f, 1.0f, zValue * 5.0f));
				}
			}
		}
	}

	labyrinthFloor = new Wall(wallIDCounter++, vec3((lastX * 0.5f), -2.0f, (lastZ * 0.5f)), finalVertices, finalNormals, finalUVs, indices);
	labyrinthFloor->SetScale(vec3(2.5f * lastX, 0.5f, 2.5f * lastZ));

	player.labyrinthWalls = labyrinthWalls;											//Pass the player every pointer to the newly created walls
}

PlayState::~PlayState()
{
	for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); it++)
	{
		delete *it;
	}
	labyrinthWalls.clear();

	delete labyrinthFloor;
	delete endChair;
}
