#pragma once
#include <glm.hpp>
#include <glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc\quaternion.hpp>
#include <gtx\euler_angles.hpp>
#include "ShaderManager.h"
#include "InputManager.h"

class Camera
{
public:
	Camera();

	void Update(float deltaTime);
	void Draw();
	void Draw2D();

	vec3 getPosition();
	vec3 getForwardVector();
	vec3 getRightVector();

	void RotateX();
	void RotateY();
	void setFreecam(bool isFreeCam);
	void setMoveVector(vec3 newForward);
	void resetMoveVector();
	void setPosition(vec3 pos);
	void setInitialPos(vec3 pos);
	bool getFreecam() { return freeCam; }

	~Camera() {}

private:
	GLuint viewID;
	GLuint viewID2D;
	GLuint positionUniformID;

	mat4 view;
	mat4 view2D;
	mat4 rotMatrixX, rotMatrixY, finalRot;

	vec3 cameraPos;
	vec3 forwardVec, positionVec, rightVec;
	vec3 lookVec;
	vec3 moveVec;
	vec2 CameraValue;

	const Uint8* keys;
	bool keyPressed;
	bool isMouseGoingUp;
	bool freeCam = false;
	float cameraSpeed, angleX, angleY, dotProduct;
};

