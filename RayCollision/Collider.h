#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vec3.h"
#include "Ray.h"
#include "AAB.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vec4.h"

struct Collider
{
// Collision detection methods:
	static bool RaySphereCollisionDetected(Ray& ray, Sphere& sphere);
	static bool RayAABCollisionDetected(Ray& ray, AAB& box);
	static bool RayAABCollisionDetected(Ray& ray, AAB& box, Vec3 PI);


// These methods return the first intersection point if there is one (closest to Ray’s starting point)

	static Vec3 RaySphereCollisionPoint(Ray& ray, Sphere& sphere);
	static Vec3 RayAABCollisionPoint(Ray& ray, AAB& box);

// Intersection of a Ray and Sphere
// Quadratic Equation: at^2 + bt + c = 0 | a= V^2, b = 2(S . V), c = S^2 - r^2

	static void quadraticEquation(Ray& ray, Sphere& sphere);


};


#endif

