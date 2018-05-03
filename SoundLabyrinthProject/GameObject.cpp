#include "GameObject.h"

GameObject::GameObject()
{
	//Getting Attributes
	vertexAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "position");
	textureAttributeID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "textureIn");
	normalID = glGetAttribLocation(TheShader::Instance()->GetShaderProgram(), "normalIn");

	//Getting Uniforms
	materialAmbientUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "material.ambient");
	materialDiffuseUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "material.diffuse");
	materialSpecularUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "material.specular");
	materialShininessUniformID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "material.shininess");

	modelID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "model");
	Textured = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "TextureFlag");
	textureUniformID1 = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "textureImage");
	isLitUniform = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "isLit");

	frequencyID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "frequency");
	timeID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "time");
	isShakingID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "isShaking");

	position = vec3(0.0f, 0.0f, 0.0f);
}

vec3 GameObject::getPos()									{ return position; }												//Returns the position of the gameObject as a vec3
void GameObject::setPos(glm::vec3 Pos)						{ position = Pos; }													//Sets the position of the gameObject
void GameObject::setBoundBox(float w, float h, float d)		{ boundBox.SetDimension(w, h, d); }									//Sets the position of the gameObject
