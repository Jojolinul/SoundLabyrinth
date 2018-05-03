#pragma once
#include <string>
#include <iostream>
#include "Singleton.h"
#include <map>
#include <glew.h>
#include <SDL_image.h>
using namespace std;

class TextureManager
{
public:

	friend class Singleton<TextureManager>;

	GLuint GetID(string name);
	bool LoadFromFile(string filename, string name);
	void UnloadFromMemory();

private:
	TextureManager() {}
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	map<string, GLuint> textureMap;
};

typedef Singleton<TextureManager> TheTexture;

