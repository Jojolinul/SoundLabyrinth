#include "stdafx.h"
#include "Chair.h"


Chair::Chair(int ID,
	vec3 chairPos,
	vector<GLfloat> finalVertices,
	vector<GLfloat> finalNormals,
	vector<GLfloat> finalUVs,
	vector<GLuint> indices)
{
	glEnable(GL_BLEND);
	chairTextureTag = "WireframeTexture";
	id = ID;

	ambient = vec3(0.1f);

	diffuse = vec3(0.2, 0.0, 0.0);
	specular = vec3(0.0, 0.0, 0.0f);
	shininess = 300.0f;

	TheShader::Instance()->setID("Chair" + to_string(id));
	TheShader::Instance()->createVAO("Chair" + to_string(id));
	TheShader::Instance()->createVertexVBO("Chair" + to_string(id));
	TheShader::Instance()->createTextureVBO("Chair" + to_string(id));
	TheShader::Instance()->createNormalVBO("Chair" + to_string(id));
	TheShader::Instance()->createEBO("Chair" + to_string(id));
	TheShader::Instance()->genBuffers("Chair" + to_string(id), finalVertices, finalNormals, finalUVs, indices);

	position = chairPos;
	boundBox.SetPosition(position.x, position.y, position.z);
	boundBox.SetDimension(5.0f, 5.0f, 5.0f);
}

void Chair::Draw()
{
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, scaleValue);

	glUniform1f(isShakingID, 0);
	glUniform1f(Textured, 1);
	glUniform1i(isLitUniform, 1);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, shininess);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->GetID(chairTextureTag));
	TheShader::Instance()->Draw("Chair" + to_string(id));
	glBindTexture(GL_TEXTURE_2D, 0);
}
