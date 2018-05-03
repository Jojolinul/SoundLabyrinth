#pragma once
#include "GameObject.h"
#include "ScreenManager.h"

class Background : public GameObject
{
public:
	Background(std::string bgID);

	void Update(float deltaTime);
	void Draw();
	glm::vec3 position;
	~Background();

private:
	GLuint VAO, VBO, EBO, vertexVBO, colorVBO, textureVBO;
	GLuint vertexAttributeID, colorAttributeID, textureAttributeID, textureUniformID1, modelID, viewID, isLitUniform;

	GLboolean Textured;

	std::string TextureBid;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	std::vector<GLfloat> UVs;


	float screenW, screenH;
	glm::mat4 model;
};

