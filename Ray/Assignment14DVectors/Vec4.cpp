#include "Vec4.h"

Vec4::Vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vec4::Vec4(float x_, float y_, float z_, float w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

float Vec4::Mag()
{
	float result;

	result = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));

	return result;
}

void Vec4::Normalize()
{
	float tempMag = Mag();

	x = x / tempMag;
	y = y / tempMag;
	z = z / tempMag;
	w = w / tempMag;
}

float Vec4::Dot(Vec4 otherVec)
{
	float tmpX = x;
	float tmpY = y;
	float tmpZ = z;
	float tmpW = w;

	tmpX = x * otherVec.x;
	tmpY = y * otherVec.y;
	tmpZ = z * otherVec.z;
	tmpW = w * otherVec.z;

	return tmpX + tmpY + tmpZ + tmpW;
}

