#include "Vec3.h"

void Vec3::Print() {
	cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

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

void Vec3::Add(const Vec3 b)
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

Vec3 Vec3::ScalarMultiplication(float scalar)
{
	Vec3 temp;

	temp.x = x * scalar;
	temp.y = y * scalar;
	temp.z = z * scalar;

	return temp;
}

float Vec3::Mag()
{
	//float result;

	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	//return result;
}

void Vec3::Normalize()
{
	float tempMag = Mag();

	x = x / tempMag;
	y = y / tempMag;
	z = z / tempMag;
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

// Operator Overloading

Vec3 Vec3::operator+ (const Vec3& v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator- (const Vec3& v) const
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator* (const float s) const
{
	return Vec3(x * s, y * s, z * s);
}

// Dot Product

float Vec3::Dot(Vec3 v)
{
	float tmpX = x;
	float tmpY = y;
	float tmpZ = z;
	
	tmpX = x * v.x;
	tmpY = y * v.y;
	tmpZ = z * v.z;

	return tmpX + tmpY + tmpZ;
}

//Cross product

Vec3 Vec3::Cross(Vec3 otherVec)
{

	float tpx = (y * otherVec.z) - (z * otherVec.y);
	float tpy = (x * -otherVec.z) - (z * -otherVec.x);
	float tpz = (x * otherVec.y) - (y * otherVec.x);
	
	//float tpy = (-x * -otherVec.z) - (-z * -otherVec.x);
	return Vec3(tpx, tpy, tpz);

	
}



