#ifndef QUATERNION_H
#define QUATERNION_H

//#include "Vec3.h"
//#include "Vec4.h"
#include "Mat3.h"

class Quaternion
{
	float w;
	Vec3 v; // Alternate: //Vec4 quaternion; ( x, y, z, w)

public:

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w_, float x_, float y_, float z_);

	void set(float w_, float x_, float y_, float z_);
	
	Quaternion(float w_, const Vec3& v);

	// Create a rotation quaternion using axis and angle
	Quaternion(Vec3 axis, float angleInDegrees);
//Methods
	// overload the * operator to multiply two quaternions
	Quaternion operator* (Quaternion otherQuat);

	// overload the operators:  + , -, =

	// Return the magnitude of the Quaternion using Pythagoras’s theorem
	float Mag();

	// Normalize the Quaternion by dividing it by it’s magnitude
	void Normalize();

	// Reverse the sign on the imaginary part of the quaternion (x, y, z)
	void Conjugate();
	
	// Invert the quaternion
	void Inverse();

	// Rotate a vector using this quaternion
	Vec3 Rotate(Vec3 vec);
	
	// Convert this quaternion into a rotation matrix
	Mat3 ConvertToMatrix();

	// Convert this quaternion into Euler angles
	EulerAngles ConvertEuler();





};

#endif