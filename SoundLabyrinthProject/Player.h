#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Wall.h"
#include <algorithm>

class Player : public GameObject
{
public:
	Player();

	void Update(float deltaTime);
	void Draw() {};

	vec3 CalculateCameraForward(Wall* col);
	vec3 CalculateCollisionDirection(vec3 direction);

	bool CheckCollision();
	bool CheckRayCollision();

	void CalculateClosestWall();
	void SetEndPosition(vec3 pos) { endPosition = pos; }

	Camera camera;
	vector<Wall*> labyrinthWalls;
	~Player();

private:
	vector<Wall*> rayCollisionWalls;
	vector<Wall*> collidedWalls;

	Ray ray;
	vec3 endPosition;

	float rayDistanceCollision;

	int oldWallID;
	int newWallID;

	double oldX, newX;
	double oldZ, newZ;
};

