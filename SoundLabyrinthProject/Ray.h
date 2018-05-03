#pragma once
#include <glm.hpp>

using namespace glm;

class Ray
{
public:
	Ray(const glm::vec3 orig, const glm::vec3 dir);
	void Update(glm::vec3 newOrigin, glm::vec3 newDirection);

	vec3 orig;
	vec3 dir;

	float sign[3];

	~Ray(){}
};

