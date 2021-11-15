#include <iostream>
#include "Vec3.h"
#include "Ray.h"

Ray::Ray() {
	start = Vec3();
	dir = Vec3();
}

Ray::Ray(Vec3 start_, Vec3 dir_)
{
	start = start_;
	dir = dir_;
}

Vec3 Ray::currentPosition(float t)
{
	//P(t) = S + tV
	return start + (dir * t);
}