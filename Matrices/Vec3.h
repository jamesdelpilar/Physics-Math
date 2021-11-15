#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <math.h>

using namespace std;

class Vec3
{
public:
	Vec3();
	Vec3(float x_, float y_, float z_);

	void Add(Vec3 b);

	void Subtract(Vec3 b);

	void ScalarMultiplication(float s);

	float Mag();

	void Normalize();

	float Dot(Vec3 b);

	void Lerp(Vec3 b, float t);

	void RotateZ(float angle);

	float x;
	float y;
	float z;

};

#endif
