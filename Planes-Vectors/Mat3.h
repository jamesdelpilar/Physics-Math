#ifndef MAT3_H
#define MAT3_H

#include <iostream>
#include <math.h>

#include "Vec3.h"

using namespace std;

class Mat3
{
public:
	Mat3();

	void Print();
	void PrintInverse();

	void SetIdentity();

	void RotateZ(float ang);

	void Scale(float x, float y, float z);

	void Transpose();

	Mat3 operator*(Mat3 otherMat);

	Vec3 operator*(Vec3 vector);

	float Det();

	Mat3 Inverse();

	float m[9];
};

#endif