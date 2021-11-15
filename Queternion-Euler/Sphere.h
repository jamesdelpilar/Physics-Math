#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"

struct Sphere
{
	Sphere(Vec3 position_, float radius_);

	Sphere();

	Vec3 position;

	float radius;
};


#endif