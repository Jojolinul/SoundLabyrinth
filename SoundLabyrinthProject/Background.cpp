#include "stdafx.h"
#include "Background.h"


Background::Background(std::string bgID)
{
	VAO = 0;
	vertexVBO = 0;
	colorVBO = 0;
	model = glm::mat4(1.0);
	TextureBid = bgID;

	screenW = TheScreen::Instance()->GetScreenSize().x;
	screenH = TheScreen::Instance()->GetScreenSize().y;

	vertexAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "position");
	colorAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "colorIn");
	textureAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "textureIn");
	isLitUniform = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "isLit");
	modelID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	Textured = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "TextureFlag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(vertexAttributeID);
	glEnableVertexAttribArray(colorAttributeID);
	glEnableVertexAttribArray(textureAttributeID);

	vertices.push_back((GLfloat)(-screenW * 0.5f));
	vertices.push_back(screenH * 0.5f);
	vertices.push_back((GLfloat)(0.0f));

	vertices.push_back((GLfloat)(screenW * 0.5f));
	vertices.push_back(screenH * 0.5f);
	vertices.push_back((GLfloat)(0.0f));

	vertices.push_back((GLfloat)(screenW * 0.5f));
	vertices.push_back(-screenH * 0.5f);
	vertices.push_back((GLfloat)(0.0f));

	vertices.push_back((GLfloat)(-screenW * 0.5f));
	vertices.push_back(-screenH * 0.5f);
	vertices.push_back((GLfloat)(0.0f));

	for (int x = 0; x < 12; x++)
	{
		colors.push_back(1.0f);
	}

	UVs.push_back(0.0f); UVs.push_back(1.0f);
	UVs.push_back(1.0f); UVs.push_back(1.0f);
	UVs.push_back(1.0f); UVs.push_back(0.0f);
	UVs.push_back(0.0f); UVs.push_back(0.0f);

	indices.push_back(0); indices.push_back(1); indices.push_back(3);
	indices.push_back(3); indices.push_back(1); indices.push_back(2);

	//VERTEX VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//COLOR VBO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(GLfloat), &UVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	position.x = screenW * 0.5f;
	position.y = screenH * 0.5f;
}

void Background::Update(float deltaTime)
{
	model = mat4(1.0);
	model = glm::translate(model, position);
}

void Background::Draw()
{
	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->GetID(TextureBid));
	glUniform1i(Textured, true);
	glUniform1i(isLitUniform, 0);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Background::~Background()
{

}
