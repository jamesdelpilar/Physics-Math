#include "Vec3.h"

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

void Vec3::Add(Vec3 b)
{
	x += b.x;
	y += b.y;
	z += b.z;
}

void Vec3::Subtract(Vec3 b)
{
	x -= b.x;
	y -= b.y;
	z -= b.z;
}

void Vec3::ScalarMultiplication(float s)
{
	x *= s;
	y *= s;
	z *= s;
}

float Vec3::Mag()
{
	float result;

	result = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	return result;
}

void Vec3::Normalize()
{
	float mag = Mag();

	x = x / mag;
	y = y / mag;
	z = z / mag;
}

float Vec3::Dot(Vec3 b)
{
	float result;

	result = (x * b.x) + (y * b.y) + (z * b.z);

	return result;
}

void Vec3::Lerp(Vec3 b, float t)
{
	x = ((1 - t) * x) + (t * b.x);
	y = ((1 - t) * y) + (t * b.y);
	z = ((1 - t) * z) + (t * b.z);
}

void Vec3::RotateZ(float angle)
{
	float tmpX, tmpY;

	tmpX = (x * cos(angle)) - (y * sin(angle));
	tmpY = (x * sin(angle)) + (y * cos(angle));

	x = tmpX;
	y = tmpY;
}

