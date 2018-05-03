#include "Camera.h"
#define upVec glm::vec3(0.0f, 1.0f, 0.0f)

Camera::Camera()
{
	viewID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "view");
	viewID2D = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "view");
	positionUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "cameraPosition");
	positionVec = vec3(0.0f, 100.0f, 0.0f);
	forwardVec = glm::vec3(0, 0, -1);
	moveVec = glm::vec3(0, 0, -1);
	cameraSpeed = 20.0f;

	keyPressed = false;
}

vec3 Camera::getRightVector()					{ return normalize(rightVec); }
vec3 Camera::getPosition()						{ return positionVec; }
vec3 Camera::getForwardVector()					{ return forwardVec; }

void Camera::setFreecam(bool isFreeCam)			{ freeCam = isFreeCam; }
void Camera::setMoveVector(vec3 newMoveVec)		{ moveVec = newMoveVec; }
void Camera::resetMoveVector()					{ moveVec = vec3(0.0f, 0.0f, -1.0f); }
void Camera::setPosition(glm::vec3 position)	{ positionVec = position; }
void Camera::setInitialPos(vec3 pos)			{ positionVec = pos; }
void Camera::Draw()								{ glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]); }
void Camera::Draw2D()							{ glUniformMatrix4fv(viewID2D, 1, GL_FALSE, &view2D[0][0]); }

void Camera::Update(float deltaTime)
{
	keys = Input::Instance()->GetKeyStates();
	view = glm::mat4(1.0);
	dotProduct = dot(lookVec, upVec);

	RotateY();																		//Horizontal rotation
	RotateX();																		//Vertical rotation
	finalRot = rotMatrixY * rotMatrixX;												// 4x4 Final Rotation Matrix calculation

	forwardVec = glm::vec3(0.0f, 0.0f, -1.0f);										//Before calculating it again, the forward vector gets reset every frame
	lookVec = glm::vec3(0.0f, 0.0f, -1.0f);											//The look vector also gets reset every frame

	forwardVec = normalize(glm::vec3(rotMatrixY * glm::vec4(forwardVec, 1)));		//Calculating the forward vector based on the horizontal rotation										
	lookVec = normalize(glm::vec3(finalRot * glm::vec4(lookVec, 1)));				//LookVec is separated from the forward, it is the one that gets sent to the shader and
																					//it is the one dealing with "free look" effect
	
	if (!freeCam)
	{
		rightVec = normalize(cross(upVec, forwardVec));								//Right vector is the cross of the static up vector and the newly calculated forward vector
		if (keys[SDL_SCANCODE_S])
		{
			positionVec += moveVec * deltaTime * -cameraSpeed;
		}
		if (keys[SDL_SCANCODE_W])
		{
			positionVec -= moveVec * deltaTime * -cameraSpeed;
		}
		if (keys[SDL_SCANCODE_A])
		{
			positionVec -= rightVec * deltaTime * (-cameraSpeed * 0.5f);
		}
		if (keys[SDL_SCANCODE_D])
		{
			positionVec += rightVec * deltaTime * (-cameraSpeed * 0.5f);
		}
	}
	else
	{
		rightVec = normalize(cross(upVec, lookVec));								//Right vector is the cross of the static up vector and the newly calculated forward vector
		if (keys[SDL_SCANCODE_S])
		{
			positionVec += lookVec * deltaTime * (-cameraSpeed * 2);
		}
		if (keys[SDL_SCANCODE_W])
		{
			positionVec -= lookVec * deltaTime * (-cameraSpeed * 2);
		}
		if (keys[SDL_SCANCODE_A])
		{
			positionVec -= rightVec * deltaTime * (-cameraSpeed * 2);
		}
		if (keys[SDL_SCANCODE_D])
		{
			positionVec += rightVec * deltaTime * (-cameraSpeed * 2);
		}
	}
	
	view = glm::lookAt(positionVec, positionVec + lookVec, upVec);
	glUniform3fv(positionUniformID, 1, &positionVec.x);
}


void Camera::RotateX()																//Stopping the vertical rotation from going over 80 degrees
{
	CameraValue.x = Input::Instance()->mouseMotion.y;

	if (CameraValue.x < CameraValue.y)isMouseGoingUp = true;
	else { isMouseGoingUp = false; }
	if (dotProduct > -0.8f && dotProduct < 0.8f)
	{
		CameraValue.y = Input::Instance()->mouseMotion.y;
		angleX = Input::Instance()->mouseMotion.y * 0.1f;
		rotMatrixX = glm::rotate(rotMatrixX, glm::radians(angleX), glm::vec3(-1.0, 0.0, 0.0));
	}
	if (dotProduct >= -0.8f && isMouseGoingUp == false)
	{
		CameraValue.y = Input::Instance()->mouseMotion.y;
		angleX = Input::Instance()->mouseMotion.y * 0.1f;
		rotMatrixX = glm::rotate(rotMatrixX, glm::radians(angleX), glm::vec3(-1.0, 0.0, 0.0));
	}

	if (dotProduct <= 0.8f && isMouseGoingUp == true)
	{
		CameraValue.y = Input::Instance()->mouseMotion.y;
		angleX = Input::Instance()->mouseMotion.y * 0.1f;
		rotMatrixX = glm::rotate(rotMatrixX, glm::radians(angleX), glm::vec3(-1.0, 0.0, 0.0));
	}

}

void Camera::RotateY()
{
	angleY = Input::Instance()->mouseMotion.x * 0.1f;
	rotMatrixY = glm::rotate(rotMatrixY, glm::radians(angleY), glm::vec3(0.0, -1.0, 0.0));
}
