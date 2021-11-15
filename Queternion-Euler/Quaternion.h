#ifndef QUATERNION_H
#define QUATERNION_H
#include"Vec3.h"	
#include "Vec4.h"
#include"EulerAngles.h"
#include "Mat3.h"
//#include "VMath.h"
//#include "Vector.h"	


struct Quaternion
{
	float w, x, y, z;
	//Vec3 v; // Alternate: //Vec4 quaternion; ( x, y, z, w)
	Vec4 quaternion;

	Quaternion();
	Quaternion(float w, float x, float y, float z);

	// Alternative
	//Quaternion(float w_, const Vec3& v); 

	// Create a rotation quaternion using axis and angle
	Quaternion(Vec3 axis, float angleInDegrees);

//Methods
	// overload the * operator to multiply two quaternions
	Quaternion operator* (Quaternion otherQ);

	// overload the operators:  + , -, =
	Quaternion operator+ (Quaternion otherQ);
	Quaternion operator- (Quaternion otherQ);
	Quaternion operator= (Quaternion otherQ);

	// Return the magnitude of the Quaternion using Pythagoras’s theorem
	float Mag();

	// Normalize the Quaternion by dividing it by it’s magnitude
	void Normalize();

	// Reverse the sign on the imaginary part of the quaternion (x, y, z)
	 Quaternion Conjugate();
	
	// Invert the quaternion
	Quaternion Inverse();

	// Rotate a vector using this quaternion
	Vec3 Rotate(Vec3 vec);
	
	// Convert this quaternion into a rotation matrix
	Mat3 ConvertToMatrix();

	// Convert this quaternion into Euler angles
	EulerAngles ConvertEuler();

};

#endif