#pragma once
#include <string>
#include <glm.hpp>
#include <glew.h>
#include <SDL.h>
#include <vector>
#include "Singleton.h"
#include "ShaderManager.h"
#include <gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class ScreenManager
{
public:
	friend class Singleton<ScreenManager>;
public:
	bool Init(string ScreenName, int w, int h, int major, int minor, bool compatible, bool fullscreen);

	void ClearScreen();
	void SwapBuffer();
	void ShutDown();
	void ShowExtentions();
	void ShowVendor();

	vec2 GetScreenSize() { return vec2(width, height); }

	void Set2DProjection();
	void Set3DProjection();

	~ScreenManager();

private:
	ScreenManager() {}
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);
private:
	vec3 backgroundColor;
	int width;
	int height;

	glm::mat4 projection;
	GLuint projectionID;
	SDL_Window* window;
	SDL_GLContext context;
};

typedef Singleton<ScreenManager> TheScreen;

