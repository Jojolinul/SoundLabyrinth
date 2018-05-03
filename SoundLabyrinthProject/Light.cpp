#include "Light.h"

Light::Light(int lightNumber)
{
	VAO = 0;
	VBO = 0;
	vertexVBO = 0;
	colorVBO = 0;

	vertexAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "position");
	colorAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "colorIn");

	modelID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	Textured = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "TextureFlag");

	lightPositionUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ("light[" + to_string(lightNumber) + "].position").c_str());
	lightAmbientUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ("light[" + to_string(lightNumber) + "].ambient").c_str());
	lightDiffuseUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ("light[" + to_string(lightNumber) + "].diffuse").c_str());
	lightSpecularUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), ("light[" + to_string(lightNumber) + "].specular").c_str());
	lightFlagUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "isLit");

	ambient = vec3(0.0f);
	diffuse = vec3(0.8f, 0.0f, 0.0f);
	specular = vec3(0);

	model = glm::mat4(1.0);
	position = vec3(0.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(vertexAttributeID);
	glEnableVertexAttribArray(colorAttributeID);

	vertices.push_back((GLfloat)(0.0f));
	vertices.push_back(0.0f);
	vertices.push_back((GLfloat)(0.0f));

	colors.push_back(1.0f);
	colors.push_back(1.0f);
	colors.push_back(1.0f);

	//VERTEX VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//COLOR VBO
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

vec3& Light::setgetPosition()				{ return position; }

void Light::setAmbient(vec3 amb)			{ ambient = amb; }
void Light::setDiffuse(vec3 dif)			{ diffuse = dif; }
void Light::setSpecular(vec3 spec)			{ specular = spec; }

void Light::Draw(bool lightVisible)
{
	glUniform3fv(lightPositionUniformID, 1, &position.x);
	glUniform3fv(lightAmbientUniformID, 1, &ambient.r);
	glUniform3fv(lightDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(lightSpecularUniformID, 1, &specular.r);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	if (lightVisible)
	{
		glPointSize(25.0f);
		glUniform1i(Textured, false);
		glUniform1i(lightFlagUniformID, false);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
	}
}

void Light::Update(float deltaTime)
{
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
}
