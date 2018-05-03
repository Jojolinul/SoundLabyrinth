#include "AABB.h"
#include <algorithm>

using namespace std;

//------------------------------------------------------------------------------------------------------
//setter function that assigns position of AABB and creates the collision box
//------------------------------------------------------------------------------------------------------
void AABB::SetPosition(float x, float y, float z)
{

	position.x = x;
	position.y = y;
	position.z = z;

	CreateBox();

}

void AABB::SetPosition2D(float x, float y)
{
	position2d.x = x;
	position2d.y = y;

	CreateBox2D();
}

//------------------------------------------------------------------------------------------------------
//setter function that assigns dimensions of AABB and creates the collision box
//------------------------------------------------------------------------------------------------------
void AABB::SetDimension(float width, float height, float depth)
{

	dimension.x = width;
	dimension.y = height;
	dimension.z = depth;

	CreateBox();

}

void AABB::SetDimension2D(float width, float height)
{
	dimension2d.x = width;
	dimension2d.y = height;

	CreateBox2D();
}
//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with another AABB object
//------------------------------------------------------------------------------------------------------
bool AABB::IsColliding(const AABB& secondBox) const
{

	return ((max.x >= secondBox.min.x && secondBox.max.x >= min.x) &&
		(max.y >= secondBox.min.y && secondBox.max.y >= min.y) &&
		(max.z >= secondBox.min.z && secondBox.max.z >= min.z));

}

bool AABB::IsColliding2D(const AABB& secondBox) const
{
	return ((max2d.x >= secondBox.min2d.x && secondBox.max2d.x >= min2d.x) &&
		(max2d.y >= secondBox.min2d.y && secondBox.max2d.y >= min2d.y));
}

//------------------------------------------------------------------------------------------------------
//function that checks if AABB collides with a Ray object
//------------------------------------------------------------------------------------------------------
bool AABB::isCollidingRay(Ray &ray, float &t)
{
	// Create another box for the ray calculation
	// ray.org is origin of ray
	float t1 = (min.x - ray.orig.x) * ray.sign[0];
	float t2 = (max.x - ray.orig.x) * ray.sign[0];
	float t3 = (min.y - ray.orig.y) * ray.sign[1];
	float t4 = (max.y - ray.orig.y) * ray.sign[1];
	float t5 = (min.z - ray.orig.z) * ray.sign[2];
	float t6 = (max.z - ray.orig.z) * ray.sign[2];

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}

//------------------------------------------------------------------------------------------------------
//function that calculates min and max values of AABB for collision purposes
//------------------------------------------------------------------------------------------------------
void AABB::CreateBox()
{
	min.x = position.x - (dimension.x / 2);
	min.y = position.y - (dimension.y / 2);
	min.z = position.z - (dimension.z / 2);

	max.x = position.x + (dimension.x / 2);
	max.y = position.y + (dimension.y / 2);
	max.z = position.z + (dimension.z / 2);
}

void AABB::CreateBox2D()
{
	min2d.x = position2d.x;
	min2d.y = position2d.y;

	max2d.x = position2d.x + dimension2d.x;
	max2d.y = position2d.y + dimension2d.y;
}
