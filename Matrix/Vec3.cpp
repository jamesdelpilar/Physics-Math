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

Vec3 Vec3::Add(Vec3 v2)
{
	x = v2.x + x;
	y = v2.y + y;
	z = v2.z + z;

	return Vec3(x, y, z); 
}

Vec3 Vec3::Subtract(Vec3 v3)
{
	x = x - v3.x;
	y = y - v3.y;
	z = z - v3.z;

	return Vec3(x, y, z);
}

Vec3 Vec3::ScalarMultiplication(float i)
{
	x = x * i;
	y = y * i;
	z = z * i;

	return Vec3(x, y, z);
}

float Vec3::Mag()
{
	return sqrt(x * x + y * y + z * z); 
}

void Vec3::Normalize()
{
	float tmpMag = Mag(); //The normalized vector v1 = (-0.104542, 0.993146, 0.0522708)
	x = x / tmpMag;
	y = y / tmpMag;
	z = z / tmpMag;
}

float Vec3::Dot(Vec3 v1)
{
	return x * v1.x + y * v1.y + z * v1.z; //The dot product of vectors result in v1 = 11.4473
}

void Vec3::Lerp(Vec3 v, float t)
{
	x = (1 - t) * x + t * v.x;
	y = (1 - t) * y + t * v.y;
	z = (1 - t) * z + t * v.z;
}

void Vec3::RotateZ(float deg)
{
	float tmpx = x;
	float tmpy = y;
	float rad = deg * M_1_PI / 180.0f; 

	x = tmpx * cos (rad) - tmpy * sin (rad);
	y = tmpx * sin (rad) + tmpy * cos (rad);

	//Not converted = (-12.9683, -0.9069, 1)
}
