#include "Wall.h"

Wall::Wall(
	int ID,
	vec3 wallPosition,
	vector<GLfloat> finalVertices,
	vector<GLfloat> finalNormals,
	vector<GLfloat> finalUVs,
	vector<GLuint> indices)

{
	glEnable(GL_BLEND);
	TextureTag = "WallTexture";
	WireframeTag = "WireframeTexture";
	wallID = ID;

	ambient = vec3(0.1f);

	diffuse = vec3(0.2, 0.0, 0.0);
	specular = vec3(0.0, 0.0, 0.0f);
	shininess = 300.0f;

	TheShader::Instance()->setID("Wall" + to_string(wallID));
	TheShader::Instance()->createVAO("Wall" + to_string(wallID));
	TheShader::Instance()->createVertexVBO("Wall" + to_string(wallID));
	TheShader::Instance()->createTextureVBO("Wall" + to_string(wallID));
	TheShader::Instance()->createNormalVBO("Wall" + to_string(wallID));
	TheShader::Instance()->createEBO("Wall" + to_string(wallID));
	TheShader::Instance()->genBuffers("Wall" + to_string(wallID), finalVertices, finalNormals, finalUVs, indices);

	position = wallPosition;
	boundBox.SetPosition(position.x, position.y, position.z);
	boundBox.SetDimension(5.0f, 5.0f, 5.0f);
}

void Wall::Draw()
{
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, scaleValue);

	glUniform1f(isShakingID, 1);
	glUniform1f(Textured, 1);
	glUniform1i(isLitUniform, 1);
	glUniform3fv(materialAmbientUniformID, 1, &ambient.r);
	glUniform3fv(materialDiffuseUniformID, 1, &diffuse.r);
	glUniform3fv(materialSpecularUniformID, 1, &specular.r);
	glUniform1f(materialShininessUniformID, shininess);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	if (isShaking)
	{
		timer += 1.0f * localDeltaTime;
		glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->GetID(WireframeTag));

		glUniform1f(timeID, time);
		glUniform1f(frequencyID, frequency);

		TheShader::Instance()->DrawWire("Wall" + to_string(wallID));
		glBindTexture(GL_TEXTURE_2D, 0);

		if (timer > 2.0f)
		{
			timer = 0;
			isShaking = false;
		}
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, TheTexture::Instance()->GetID(TextureTag));

		glUniform1f(Textured, 1);
		glUniform1i(isLitUniform, 1);
		glUniform1f(isShakingID, 0);

		TheShader::Instance()->Draw("Wall" + to_string(wallID));

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Wall::Update(float deltaTime)
{
	time += deltaTime;
	localDeltaTime = deltaTime;
}
