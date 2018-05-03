#pragma once
#include <string>
#include <vector>
#include <glew.h>
#include <glm.hpp>

//struct to store all three components of a vertex group, which is
//the grouping of verts, UVs and norms for each point in a triangle
struct Groups
{
	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;
};

class OBJLoader
{

public:

	OBJLoader() {};
	~OBJLoader() {};

	bool LoadModel(const std::string& filename, std::vector<GLfloat> &vertices, std::vector<GLfloat> &normals, std::vector<GLfloat> &textures, std::vector<GLuint> &indices);

private:


};