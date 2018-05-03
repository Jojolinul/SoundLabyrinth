#pragma once
#include <iostream>
#include <string.h>
#include <glew.h>
#include "Singleton.h"
#include <glm.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace glm;

class ShaderManager
{
public:
	friend class Singleton<ShaderManager>;

public:
	bool CreateProgram();
	bool CreateShaders();
	bool CompileShaders(std::string fileName, int var);
	void AttachShaders();
	bool LinkProgram();

	GLuint ShaderManager::GetShaderProgram();

	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();
	~ShaderManager();

	void setID(string name);

	void createVAO(string name);
	void createVertexVBO(string name);
	void createTextureVBO(string name);
	void createNormalVBO(string name);
	void createColourVBO(string name);
	void createEBO(string name);
	void genBuffers(string name, vector<GLfloat> finalVertices, vector<GLfloat> finalNormals,
		vector<GLfloat> finalUVs, vector<GLuint> indices);

	void gen2DBuffers(string name, vector<GLfloat> finalVertices, vector<GLfloat> finalNormals,
		vector<GLfloat> finalUVs, vector<GLuint> indices, vector<GLuint> colour);

	void Draw(string name);
	void DrawWire(string name);

private:

	ShaderManager() {}
	ShaderManager(const ShaderManager&);
	ShaderManager& operator=(const ShaderManager&);

private:
	map<string, GLuint> VAO;
	map<string, GLuint> vertexVBO;
	map<string, GLuint> textureVBO;
	map<string, GLuint> normalVBO;
	map<string, GLuint> colourVBO;
	map<string, GLuint> EBO;

	map<string, GLuint> vertexAttributeID;
	map<string, GLuint> normalID;
	map<string, GLuint> colourID;
	map<string, GLuint> textureAttributeID;
	map<string, GLuint> nrVerts;

	GLuint shaderProgramID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

typedef Singleton<ShaderManager> TheShader;
