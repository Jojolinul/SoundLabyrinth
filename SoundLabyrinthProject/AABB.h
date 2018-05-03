#pragma once
#include <glm.hpp>
#include "Ray.h"

class AABB
{
public:
	AABB() {}

	void SetPosition(float x, float y, float z);
	void SetPosition2D(float x, float y);

	void SetDimension(float width, float height, float depth);
	void SetDimension2D(float width, float height);

	glm::vec3 getDimension() { return (glm::vec3(dimension.x, dimension.y, dimension.z)); }
	glm::vec3 getHalfDimension() { return (glm::vec3(dimension.x, dimension.y, dimension.z) * 0.5f); }

	bool IsColliding(const AABB& secondBox) const;
	bool IsColliding2D(const AABB& secondBox) const;
	bool isCollidingRay(Ray &r, float &t);

private:

	void CreateBox2D();
	vec2 min2d;
	vec2 max2d;
	vec2 position2d;
	vec2 dimension2d;

	void CreateBox();
	vec3 min;
	vec3 max;
	vec3 position;
	vec3 dimension;

};

