#include "stdafx.h"
#include "Player.h"
#include "AABB.h"
#include "Tool.h"
#include <math.h>
#include <algorithm>
#include "AudioManager.h"

using namespace std;

#define UPVEC vec3(0.0f, 1.0f, 0.0f)

Player::Player() : ray(camera.getPosition(), camera.getForwardVector())
{
	labyrinthWalls.clear();

	camera.setInitialPos(vec3(500.0f, 500.0f, 500.0f));
	boundBox.SetDimension(2.0f, 2.0f, 2.0f);
}

void Player::Update(float deltaTime)													//Update all components that Player contains, also check for the collision detection
{																						//and set the camera's move vector based on the collision normals
	position = camera.getPosition();
	boundBox.SetPosition(position.x, position.y, position.z);
	ray.Update(camera.getPosition(), camera.getForwardVector());

	if (Input::Instance()->GetLeftButtonState()) {										//Check for mouse click and do the ray collision detection and calculate the closest																				//wall to the player, also play the sound effect while in the CalculateClosestWall() method
		if (CheckRayCollision())
			CalculateClosestWall();
	}
	else	rayCollisionWalls.clear();													//When mouse click is released clear the vector that contains all the walls that collided with the ray

	if (!camera.getFreecam())															//If camera is not in "Freecam" mode do the collision detection for the walls, get the collision normal
	{																					//and add them for every collision found in that frame (can be more than one wall if you are sliding from
		if (CheckCollision())															//one wall to another
		{
			vec3 allCollisionNormals;
			for (auto it = collidedWalls.begin(); it != collidedWalls.end(); it++)
			{
				allCollisionNormals += CalculateCameraForward((*it));
			}

			camera.setMoveVector(allCollisionNormals);
			camera.setPosition(vec3(oldX, 1.0f, oldZ));
		}
		else
		{
			camera.setMoveVector(camera.getForwardVector());							//Also I save the last "X" and "Z" value for the camera when a collision was not detected so that I can
			oldX = camera.getPosition().x;												//revert back to it after one frame of collision
			oldZ = camera.getPosition().z;
		}

		camera.Update(deltaTime);
		collidedWalls.clear();
	}
	else camera.Update(deltaTime);

}

bool Player::CheckCollision()															//Loop through all the walls in the scene and check if they are colliding with the player
{
	for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); ++it)
	{
		if (boundBox.IsColliding((*it)->getBoundBox()))
		{
			collidedWalls.push_back((*it));												//If collision is found add the pointer to the wall to a container
		}
	}

	if (collidedWalls.empty()) return false;
	else					  return true;
}

bool Player::CheckRayCollision()														//Loop through all the walls in the scene and check if they are colliding with the ray
{
	for (auto it = labyrinthWalls.begin(); it != labyrinthWalls.end(); ++it)
	{
		if ((*it)->getBoundBox().isCollidingRay(ray, rayDistanceCollision))
		{
			rayCollisionWalls.push_back((*it));											//If collision is found add the pointer to the wall to a container
		}
	}

	if (rayCollisionWalls.empty()) return false;
	else						   return true;
}

void Player::CalculateClosestWall()
{
	if (!rayCollisionWalls.empty())														//Even though I already check if there is a collision with a ray it's always better to
	{																					//check twice just in case there's a pointer that is not supposed to be there
		int wallIndex;
		float wallDistance = INFINITY;
		for (auto it = rayCollisionWalls.begin(); it != rayCollisionWalls.end(); it++)	//Generic algorithm to calculate which wall is the closest one from the ones I collided with
		{																				//This is necesary because my Ray implementation doesn't involve a length, so the ray travels
			float tempDistance;															//throughout the view frustum colliding with multiple walls.
			tempDistance = glm::length((*it)->getPos() - camera.getPosition());
			if (tempDistance < wallDistance)
			{
				wallDistance = tempDistance;
				wallIndex = it - rayCollisionWalls.begin();
			}
		}

		if (wallDistance > 8.0f)														//Check for the wallDistance before doing calculations, saves performance
			return;

		auto it = rayCollisionWalls.begin() + wallIndex;								//Move the index in the vector to the closest wall index
		newWallID = (*it)->WallID();

		if (newWallID != oldWallID)														//Check if the current wall I am colliding is not the old wall
		{
			float distanceToExit = glm::length(endPosition - camera.getPosition());		//Start calculating all the pitch values and frequency that the wall collided with has to start
			distanceToExit = glm::clamp((distanceToExit / 5) - 3, 0.5f, 100.0f);		//shaking on

			Audio::Instance()->PlaySounds("click.wav", distanceToExit);

			oldWallID = newWallID;
			(*it)->SetFrequency(glm::clamp(distanceToExit*0.1f, 0.1f, 120.0f));
			(*it)->IsShaking() = true;
		}
	}
}

vec3 Player::CalculateCameraForward(Wall* col)											//This is where I sort of fake the collision detection, because my whole scene is based on
{																						//cubes this is so much easier without a propper collision engine
	vec3 colisionNormal;
	vec3 aabbHalfDimension = col->getBoundBox().getHalfDimension();

	if ((position.x < col->getPos().x) && (camera.getForwardVector().x >= 0) && ((position.z < col->getPos().z + aabbHalfDimension.z) && (position.z >= col->getPos().z - aabbHalfDimension.z)))
	{
		colisionNormal = vec3(1.0f, 0.0f, 0.0f);
	}
	else if ((position.x >= col->getPos().x) && (camera.getForwardVector().x < 0) && ((position.z < col->getPos().z + aabbHalfDimension.z) && (position.z >= col->getPos().z - aabbHalfDimension.z)))
	{
		colisionNormal = vec3(-1.0f, 0.0f, 0.0f);
	}
	else if ((position.z < col->getPos().z) && (camera.getForwardVector().z >= 0) && ((position.x < col->getPos().x + aabbHalfDimension.x) && (position.x >= col->getPos().x - aabbHalfDimension.x)))
	{
		colisionNormal = vec3(0.0f, 0.0f, -1.0f);
	}
	else if ((position.z >= col->getPos().z) && (camera.getForwardVector().z < 0) && ((position.x < col->getPos().x + aabbHalfDimension.x) && (position.x >= col->getPos().x - aabbHalfDimension.x)))
	{
		colisionNormal = vec3(0.0f, 0.0f, 1.0f);
	}

	if (colisionNormal == vec3(0.0f))	return vec3(0.0f);
	else								return	CalculateCollisionDirection(normalize(cross(UPVEC, colisionNormal)));
}

vec3 Player::CalculateCollisionDirection(vec3 direction)								//Calculate which way I have to apply the force based on the dot product between the player
{																						//camera and the right vector of the collision
	float sign = Sign(dot(direction, camera.getForwardVector()));
	return direction * sign;
}


Player::~Player()
{
	for (auto it = rayCollisionWalls.begin(); it != rayCollisionWalls.end(); it++)
	{
		delete (*it);
	}
	for (auto it = collidedWalls.begin(); it != collidedWalls.end(); it++)
	{
		delete (*it);
	}

	labyrinthWalls.clear();
	rayCollisionWalls.clear();
	collidedWalls.clear();
}
