#include "Ray.h"

Ray::Ray(const glm::vec3 orig, const glm::vec3 dir)
{
	sign[0] = 1.0f / dir.x;
	sign[1] = 1.0f / dir.y;
	sign[2] = 1.0f / dir.z;
}

void Ray::Update(glm::vec3 newOrigin, glm::vec3 newDirection)
{
	orig = newOrigin;
	dir = newDirection;

	sign[0] = 1.0f / dir.x;
	sign[1] = 1.0f / dir.y;
	sign[2] = 1.0f / dir.z;
}
