#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall(int ID,								//Saves me a lot of time from loading the wall 3D model
		vec3 wallPosition,						//Otherwise I would have to open the obj and read it for every wall
		vector<GLfloat> finalVertices,			//Which is really bad for the initial start-up since it makes everything really slow
		vector<GLfloat> finalNormals,
		vector<GLfloat> finalUVs,
		vector<GLuint> indices);

	void Update(float deltaTime);
	void Draw();

	void SetScale(vec3 scale)		{ scaleValue = scale; }
	void SetFrequency(float freq)	{ frequency = freq; }
	bool& IsShaking()				{ return isShaking; }
	int& WallID()					{ return wallID; }

	~Wall() {}

private:
	string TextureTag;
	string WireframeTag;

	vec3 scaleValue = vec3(5.0f);

	bool isShaking = false;

	int wallID;
	float frequency;
	float timer;
	float localDeltaTime;
	float time;
};

