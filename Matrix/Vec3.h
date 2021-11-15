#ifndef VEC3_H
#define VEC3_H
#include <math.h>
#define _USE_MATH_DEFINES
#include <iostream>

struct Vec3
{
	Vec3();
	Vec3(float x_, float y_, float z_);

	float x;
	float y;
	float z;

	Vec3 Add(Vec3);

	Vec3 Subtract(Vec3);

	Vec3 ScalarMultiplication(float i); 
	
	float Mag();

	void Normalize();

	float Dot(Vec3);

	void Lerp(Vec3, float);

	void RotateZ(float);

};

#endif

