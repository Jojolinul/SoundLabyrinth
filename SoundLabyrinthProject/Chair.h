#pragma once
#include "GameObject.h"
class Chair :
	public GameObject
{
public:
	Chair(int ID,
		vec3 chairPos,
		vector<GLfloat> finalVertices,
		vector<GLfloat> finalNormals,
		vector<GLfloat> finalUVs,
		vector<GLuint> indices);

	void Update(float deltaTime) {}
	void Draw();

	~Chair() {}

private:
	vec3 scaleValue = vec3(5.0f);
	string chairTextureTag;

	int id;
};

