#pragma once
#include "GameState.h"
#include <gtc\quaternion.hpp>
#include <gtx\euler_angles.hpp>
#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include <vector>
#include "Chair.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "Light.h"
#include "Wall.h"
#include "Player.h"
#include "AABB.h"
#include "Background.h"

class PlayState : public GameState
{

public:
	PlayState();

	bool Update(double deltaTime);
	bool Draw();

	~PlayState();

private:
	void CreateLabyrinth();

	Light playerLight;
	Camera cam;
	Player player;

	OBJLoader labyrinthWall_Object;
	OBJLoader chair_Object;

	Wall* labyrinthFloor;
	Chair* endChair;

	vector<string> labyrinthData;
	vector<Wall*> labyrinthWalls;

	vector<GLuint> indices;
	vector<GLfloat> finalVertices;
	vector<GLfloat> finalUVs;
	vector<GLfloat> finalNormals;

	vector<GLuint> chairIndices;
	vector<GLfloat> chairFinalVertices;
	vector<GLfloat> chairFinalUVs;
	vector<GLfloat> chairFinalNormals;

	GLuint fogID;
	GLuint AttenuationID;

	const Uint8* keys = nullptr;

	bool showIntro = true;

	float fogAmount = -2.0f;
	float attenuationAmount = 0.5f;
	float deltaTimeCount;
};


