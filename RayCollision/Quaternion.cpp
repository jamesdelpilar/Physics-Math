#include "Quaternion.h"

Quaternion::Quaternion()
{
	set(1, 0.0f, 0.0f, 0.0f);
}


void Quaternion::set(float w_, float x_, float y_, float z_)
{
	
w = w_;
v.x = x_;
v.y = y_;
v.z = z_;
	
}

Quaternion::Quaternion(float w_, const Vec3& v)
{
	set(w_, v.x, v.y, v.z);
}

Quaternion::Quaternion(Vec3 axis, float angleInDegrees)
{
}

Quaternion Quaternion::operator*(Quaternion otherQuat)
{
	Vec3 ijk(w * q.v + q.w * V + VMath::cross(v, q.v));

	return Quaternion();
}

float Quaternion::Mag()
{
	return 0.0f;
}

void Quaternion::Normalize()
{
}

void Quaternion::Conjugate()
{
}

void Quaternion::Inverse()
{
}

Vec3 Quaternion::Rotate(Vec3 vec)
{
	return Vec3();
}

Mat3 Quaternion::ConvertToMatrix()
{
	return Mat3();
}

EulerAngles Quaternion::ConvertEuler()
{
	return EulerAngles();
}
