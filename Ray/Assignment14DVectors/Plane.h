#ifndef PLANE_H
#define PLANE_H

#include "Vec4.h"
#include "Ray.h"

class Plane {
public:

	Vec4 plane;
	//Default Constructor
	Plane();
	~Plane();
	// Member Variables
	float x;
	float y;
	float z;
	float w;

	// Starting position of ray
	Vec3 start;

	// Direction of ray
	Vec3 dir;

	// Set the member variables of the plane
	Plane(float x_, float y_, float z_, float d_);
	
	// Define the plane using three points that are on the plane
	Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2);

	// Find the intersection point of a ray passing through this plane
	Vec3 intersectionPoint(Ray ray);

	
};

#endif
