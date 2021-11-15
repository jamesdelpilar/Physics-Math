#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include "Vec3.h"

using namespace std;

class Vec4 : public Vec3
{
public:
	Vec4();

	// Member Variables
	float x;
	float y;
	float z;
	float w;

	// Constructors
	Vec4(float x_, float y_, float z_, float w_);

	float Mag();
	void Normalize();
	float Dot(Vec4 otherVec);

	Vec3 Start;
	Vec3 dir;

};


#endif












