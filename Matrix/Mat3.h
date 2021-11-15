#ifndef MAT3_H
#define MAT3_H
#include <iostream>
#include <math.h>

struct Mat3
{
	void Print();

	float m[9];

	Mat3();

	void SetIdentity();

	void RotateZ(float);

	void Scale(float, float, float);

	void Transpose();


};
#endif