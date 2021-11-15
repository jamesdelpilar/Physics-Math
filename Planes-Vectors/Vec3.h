#ifndef VEC3_H
#define VEC3_H

#include <iostream>


using namespace std;

class Vec3
{
public:
	
	void Print();

	Vec3();

	// Member Variables
	float x;
	float y;
	float z;

	// Constructors
	Vec3(float x_, float y_, float z_);

	//Operator Overloading
	Vec3 operator+ (const Vec3& v) const;

	Vec3 operator- (const Vec3& v) const;

	Vec3 operator* (const float s) const;

	Vec3 ScalarMultiplication(float scalar);

	void Add(Vec3 b);

	void Subtract(Vec3 b);

	float Mag();

	void Normalize();

	void Lerp(Vec3 b, float t);

	void RotateZ(float angle);

	float Dot(Vec3 v);

	Vec3 Cross(Vec3 otherVec);
};

#endif

