#include "ScreenManager.h"
#include <iostream>
#include <string>

using namespace std;

bool ScreenManager::Init(string ScreenName, int w, int h, int major, int minor, bool compatible, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	width = w;
	height = h;

	//Initialising colour buffers
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Enable double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Set a core profile
	if (!compatible) { SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); }
	else { SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); }

	//FullScreen or Not FullScreen
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		: SDL_WINDOW_OPENGL;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

	//Create game window
	window = SDL_CreateWindow(ScreenName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, screenFlag);
	context = SDL_GL_CreateContext(window);
	glEnable(GL_DEPTH_TEST);

	if (window == 0)
	{
		return false;
	}
	if (context == 0)
	{
		return false;
	}

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//TRANSPARENCY
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void ScreenManager::Set2DProjection()
{
	glDisable(GL_DEPTH_TEST);
	projectionID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "projection");
	projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
}

void ScreenManager::Set3DProjection()
{
	glEnable(GL_DEPTH_TEST);
	projectionID = glGetUniformLocation(TheShader::Instance()->GetShaderProgram(), "projection");
	projection = glm::perspective(glm::radians(68.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);
}

void ScreenManager::ClearScreen()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void ScreenManager::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}

void ScreenManager::ShowExtentions()
{
	GLint numExtensions;
	std::vector<std::string> extensions;

	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
	for (int i = 0; i < numExtensions; i++)
	{
		string s = (const char*)glGetStringi(GL_EXTENSIONS, i);
		extensions.push_back(s);
	}

	for (int i = 0; i < extensions.size(); i++)
	{
		cout << i << " : " << extensions[i] << endl;
	}
}

void ScreenManager::ShutDown()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ScreenManager::ShowVendor()
{
	cout << (const char*)(glGetString(GL_VENDOR)) << endl;
	cout << (const char*)(glGetString(GL_RENDERER)) << endl;
	cout << (const char*)(glGetString(GL_VERSION)) << endl;
	cout << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION)) << endl;
}

ScreenManager::~ScreenManager()
{

}
