#pragma once
#include <SDL.h>
#include <vector>
#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <glew.h>
#include "ShaderManager.h"
#include "TextureManager.h"
#include "OBJLoader.h"
#include "AABB.h"

class GameObject
{
public:
	GameObject();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	virtual vec3 getPos();
	virtual AABB getBoundBox() { return boundBox; }

	virtual void setPos(glm::vec3 position);
	virtual void setBoundBox(float width, float height, float depth);

	virtual ~GameObject() = 0 {};

protected:
	mat4 model;

	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	AABB boundBox;

	GLboolean Textured;
	GLboolean isShakingID;

	GLuint frequencyID;
	GLuint timeID;
	GLuint vertexAttributeID;
	GLuint textureAttributeID;
	GLuint textureUniformID1;
	GLuint isLitUniform;
	GLuint modelID;
	GLuint viewID;
	GLuint normalID;
	GLuint materialAmbientUniformID;
	GLuint materialDiffuseUniformID;
	GLuint materialSpecularUniformID;
	GLuint materialShininessUniformID;

	float shininess;
};