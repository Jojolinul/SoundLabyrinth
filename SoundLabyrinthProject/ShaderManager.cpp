#include "ShaderManager.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool ShaderManager::CreateProgram()
{
	shaderProgramID = glCreateProgram();

	if (shaderProgramID == 0)
	{
		cout << "Shader Program not created" << endl;
		return false;
	}
	return true;
}

bool ShaderManager::CreateShaders()
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
	{
		cout << "Vertex shader not created" << endl;
		return false;
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (fragmentShaderID == 0)
	{
		cout << "Fragment shader not created" << endl;
		return false;
	}
	return true;
}

bool ShaderManager::CompileShaders(std::string fileName, int var)
{
	fstream file;
	string lineText = "";
	string finalString = "";
	GLuint vertfragC;

	file.open(fileName);
	if (!file)
	{
		cout << fileName << " not opened" << endl;
	}

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + "\n";
	}
	file.close();

	const GLchar* finalCode = static_cast<const GLchar*>(finalString.c_str());

	if (var == 0) { vertfragC = vertexShaderID; }
	if (var == 1) { vertfragC = fragmentShaderID; }

	glShaderSource(vertfragC, 1, &finalCode, NULL);
	glCompileShader(vertfragC);
	GLint compileResult;

	glGetShaderiv(vertfragC, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE) { cout << "Vertex Shader compiled OK" << endl; }
	if (compileResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetShaderInfoLog(vertfragC, 1000, &length, error);
		cout << error << endl;
	}

	return true;
}

void ShaderManager::AttachShaders()
{
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
}

bool ShaderManager::LinkProgram()
{
	glLinkProgram(shaderProgramID);
	glUseProgram(shaderProgramID);

	GLint linkResult;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(shaderProgramID, 1000, &length, error);
		cout << error << endl;

		return false;
	}
	return true;
}

GLuint ShaderManager::GetShaderProgram()
{

	return shaderProgramID;
}

void ShaderManager::DetachShaders()
{
	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);
}
void ShaderManager::DestroyShaders()
{
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
void ShaderManager::DestroyProgram()
{
	glDeleteProgram(shaderProgramID);
}

void ShaderManager::createVAO(string name)
{
	GLuint tempVAO = 0;
	VAO[name] = tempVAO;
}

void ShaderManager::createVertexVBO(string name)
{
	GLuint tempVBO = 0;
	vertexVBO[name] = tempVBO;
}

void ShaderManager::createTextureVBO(string name)
{
	GLuint tempVBO = 0;
	textureVBO[name] = tempVBO;
}

void ShaderManager::createNormalVBO(string name)
{
	GLuint tempVBO = 0;
	normalVBO[name] = tempVBO;
}

void ShaderManager::createEBO(string name)
{
	GLuint tempEBO = 0;
	EBO[name] = tempEBO;
}

void ShaderManager::createColourVBO(string name)
{
	GLuint tempVBO = 0;
	colourVBO[name] = tempVBO;
}

void ShaderManager::genBuffers(string name, vector<GLfloat> finalVertices, vector<GLfloat> finalNormals,
	vector<GLfloat> finalUVs, vector<GLuint> indices)
{
	glDeleteVertexArrays(1, &VAO[name]);
	glDeleteBuffers(1, &vertexVBO[name]);
	glDeleteBuffers(1, &textureVBO[name]);
	glDeleteBuffers(1, &normalVBO[name]);
	glDeleteBuffers(1, &EBO[name]);


	nrVerts[name] = indices.size();
	glGenVertexArrays(1, &VAO[name]);
	glBindVertexArray(VAO[name]);
	glGenBuffers(1, &vertexVBO[name]);
	glGenBuffers(1, &textureVBO[name]);
	glGenBuffers(1, &normalVBO[name]);
	glGenBuffers(1, &EBO[name]);

	//Vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(GLfloat), &finalVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexAttributeID[name]);
	glVertexAttribPointer(vertexAttributeID[name], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals VBO
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalNormals.size() * sizeof(GLfloat), &finalNormals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalID[name]);
	glVertexAttribPointer(normalID[name], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalUVs.size() * sizeof(GLfloat), &finalUVs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(textureAttributeID[name]);
	glVertexAttribPointer(textureAttributeID[name], 2, GL_FLOAT, GL_FALSE, 0, 0);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[name]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void ShaderManager::gen2DBuffers(string name, vector<GLfloat> finalVertices, vector<GLfloat> finalNormals,
	vector<GLfloat> finalUVs, vector<GLuint> indices, vector<GLuint> colour)
{
	glDeleteVertexArrays(1, &VAO[name]);
	glDeleteBuffers(1, &vertexVBO[name]);
	glDeleteBuffers(1, &textureVBO[name]);
	glDeleteBuffers(1, &normalVBO[name]);
	glDeleteBuffers(1, &colourVBO[name]);
	glDeleteBuffers(1, &EBO[name]);


	nrVerts[name] = indices.size();
	glGenVertexArrays(1, &VAO[name]);
	glBindVertexArray(VAO[name]);
	glGenBuffers(1, &vertexVBO[name]);
	glGenBuffers(1, &textureVBO[name]);
	glGenBuffers(1, &normalVBO[name]);
	glGenBuffers(1, &colourVBO[name]);
	glGenBuffers(1, &EBO[name]);

	//Vertex VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(GLfloat), &finalVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexAttributeID[name]);
	glVertexAttribPointer(vertexAttributeID[name], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals VBO
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalNormals.size() * sizeof(GLfloat), &finalNormals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalID[name]);
	glVertexAttribPointer(normalID[name], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//COLOR VBO
	glBindBuffer(GL_ARRAY_BUFFER, colourVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, colour.size() * sizeof(GLfloat), &colour[0], GL_STATIC_DRAW);
	glVertexAttribPointer(colourID[name], 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture VBO
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO[name]);
	glBufferData(GL_ARRAY_BUFFER, finalUVs.size() * sizeof(GLfloat), &finalUVs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(textureAttributeID[name]);
	glVertexAttribPointer(textureAttributeID[name], 2, GL_FLOAT, GL_FALSE, 0, 0);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[name]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void ShaderManager::setID(string name)
{
	vertexAttributeID[name] = glGetAttribLocation(shaderProgramID, "position");
	normalID[name] = glGetAttribLocation(shaderProgramID, "normalIn");
	textureAttributeID[name] = glGetAttribLocation(shaderProgramID, "textureIn");
}

void ShaderManager::Draw(string name)
{
	glBindVertexArray(VAO[name]);
	glDrawElements(GL_TRIANGLES, nrVerts[name], GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ShaderManager::DrawWire(string name)
{
	glLineWidth(3.0f);

	glBindVertexArray(VAO[name]);
	glDrawElements(GL_LINES, nrVerts[name], GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


ShaderManager::~ShaderManager()
{
}

