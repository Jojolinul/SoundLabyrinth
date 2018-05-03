#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <glew.h>
#include "ShaderManager.h"
#include "InputManager.h"
#include "TextureManager.h"

class Light
{
public:
	Light(int lightNumber);
	void Update(float deltaTime);
	void Draw(bool lightVisible);

	vec3& setgetPosition();

	void setAmbient(vec3 ambient);
	void setDiffuse(vec3 diffuse);
	void setSpecular(vec3 specular);

	~Light() {}

private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 cameraPos;

	mat4 model;

	GLuint VAO;
	GLuint VBO;
	GLuint vertexVBO;
	GLuint colorVBO;

	GLuint vertexAttributeID;
	GLuint colorAttributeID;
	GLuint lightPositionUniformID;
	GLuint lightAmbientUniformID;
	GLuint lightDiffuseUniformID;
	GLuint lightSpecularUniformID;
	GLuint lightFlagUniformID;
	GLuint modelID;

	GLboolean Textured;

	vector<GLfloat> colors;
	vector<GLfloat> vertices;
	vector<unsigned int> indices;
	vector<GLfloat> UVs;

	float angle, mixValue;
};

