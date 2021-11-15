#include "Quaternion.h"
#include  "EulerAngles.h"
#include <cmath>

Quaternion::Quaternion()
{
	quaternion.x = 0.0f;
	quaternion.y = 0.0f;
	quaternion.z = 0.0f;
	quaternion.w = 1.0f;

}



Quaternion::Quaternion(float x_, float y_, float z_, float w_)
{
	quaternion.x = x_;
	quaternion.y = y_;
	quaternion.z = z_;
	quaternion.w = w_;

}

// Alternative
//Quaternion::Quaternion(float w_, const Vec3& v)
//{
//}


Quaternion::Quaternion(Vec3 axis, float angleInDegrees)
{
	// Convert to Radians
	float PI = 3.14159265358979323846f;
	float rad = PI * angleInDegrees / 180.0f;

	axis.Normalize();

	quaternion.w = cos(rad / 2.0f);
	quaternion.x = sin(rad / 2.0f) * axis.x;
	quaternion.y = sin(rad / 2.0f) * axis.y;
	quaternion.z = sin(rad / 2.0f) * axis.z;

}

Quaternion Quaternion::operator* (Quaternion otherQ) // Quaternion = Quaternion * Quaternion | Function
{
	//Vec3 vec = w * (q.v + q.w) * v + Vec3::Cross(q.v);
	//float s = quaternion.w * q.w - Vec3::Dot(q.v);
	//return Quaternion(s, vec);
	//Vec3 tempV = Vec3(quaternion.x, quaternion.y, quaternion.z);

	/*quaternion.w = ((quaternion.w * otherQ.quaternion.w) - (quaternion.x * otherQ.quaternion.x) - (quaternion.y * otherQ.quaternion.y) - (quaternion.z * otherQ.quaternion.z));
	quaternion.x = ((quaternion.w * otherQ.quaternion.x) + (quaternion.x * otherQ.quaternion.w) + (quaternion.y * otherQ.quaternion.z) - (quaternion.z * otherQ.quaternion.y));
	quaternion.y = ((quaternion.w * otherQ.quaternion.y) - (quaternion.x * otherQ.quaternion.z) + (quaternion.y * otherQ.quaternion.w) + (quaternion.z * otherQ.quaternion.x));
	quaternion.z = ((quaternion.w * otherQ.quaternion.z) + (quaternion.x * otherQ.quaternion.y) - (quaternion.y * otherQ.quaternion.x) + (quaternion.z * otherQ.quaternion.w));
	return Quaternion(quaternion.w, quaternion.x, quaternion.y, quaternion.z);*/


	Vec3 testV1 = Vec3(quaternion.x, quaternion.y, quaternion.z);
	Vec3 testV2 = Vec3(otherQ.quaternion.x, otherQ.quaternion.y, otherQ.quaternion.z);
	float w = (quaternion.w * otherQ.quaternion.w) - testV1.Dot(testV2);
	Vec3 v = (testV2 * quaternion.w) + (testV1 * otherQ.quaternion.w) + (testV1.Cross(testV2));
	return Quaternion(v.x, v.y, v.z, w);

	/*Vec3 v1 = Vec3(x, y, z);
	Vec3 v2 = Vec3(q.x, q.y, q.z);
	float w = (q.w * q.w) - v1.Dot(v2);
	Vec3 v = (v2 * q.w) + (v1 * q.w) + (v1.Cross(v2));
	return Quaternion(v.x, v.y, v.z, w);*/
}


Quaternion Quaternion::operator+(Quaternion otherQ)
{
	return Quaternion(quaternion.w + otherQ.w, quaternion.x + otherQ.x, y + otherQ.y, quaternion.z + otherQ.z);
}

Quaternion Quaternion::operator-(Quaternion otherQ)
{
	return Quaternion(quaternion.w - otherQ.w, quaternion.x - otherQ.x, y - otherQ.y, quaternion.z - otherQ.z);
}

Quaternion Quaternion::operator=(Quaternion otherQ)
{
	
	quaternion.w = otherQ.w;
	quaternion.x = otherQ.x;
	quaternion.y = otherQ.y;
	quaternion.z = otherQ.z;

	return Quaternion();
}

float Quaternion::Mag()
{
	return sqrt((quaternion.w * quaternion.w)+ (quaternion.x * quaternion.x) + (quaternion.y * quaternion.y) + (quaternion.z * quaternion.z));
}

void Quaternion::Normalize()
{
	quaternion.w /= Mag();
	quaternion.x /= Mag();
	quaternion.y /= Mag();
	quaternion.z /= Mag();
}

Quaternion Quaternion::Conjugate()
{
	quaternion = Vec4(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
	return Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

Quaternion Quaternion::Inverse() // q^-1 = q* / ||q||^2 
{
	Quaternion q(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
	Quaternion conjugate = q.Conjugate();
	float magnitude = q.Mag() * q.Mag();

	q.quaternion.x = conjugate.quaternion.x / magnitude;
	q.quaternion.y = conjugate.quaternion.y / magnitude;
	q.quaternion.z = conjugate.quaternion.z / magnitude;
	q.quaternion.w = conjugate.quaternion.w / magnitude;

	return q;
}

Vec3 Quaternion::Rotate(Vec3 vec) // qPQ^-1
{
	Quaternion q = Quaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
	Quaternion P = Quaternion(vec.x, vec.y, vec.z, 0.0f);
	Quaternion Q = q * P * q.Inverse();

	return Vec3(Q.quaternion.x, Q.quaternion.y, Q.quaternion.z);
}

Mat3 Quaternion::ConvertToMatrix()
{
	Mat3 temp;
	
	temp.m[0] = 1 - (2 * quaternion.y * quaternion.y) - (2 * quaternion.z * quaternion.z);
	temp.m[1] = (2 * quaternion.x * quaternion.y) - (2 * quaternion.w * quaternion.z);
	temp.m[2] = (2 * quaternion.x * quaternion.z) + (2 * quaternion.w * quaternion.y);
	temp.m[3] = (2 * quaternion.x * quaternion.y) + (2 * quaternion.w * quaternion.z);
	temp.m[4] = 1 - (2 * quaternion.x * quaternion.x) - (2 * quaternion.z * quaternion.z);
	temp.m[5] = (2 * quaternion.y * quaternion.z) - (2 * quaternion.w * quaternion.x);
	temp.m[6] = (2 * quaternion.x * quaternion.z) - (2 * quaternion.w * quaternion.y);
	temp.m[7] = (2 * quaternion.y * quaternion.z) + (2 * quaternion.w * quaternion.x);
	temp.m[8] = 1 - (2 * quaternion.x * quaternion.x) - (2 * quaternion.y * quaternion.y);
	
	return temp;
}

EulerAngles Quaternion::ConvertEuler()
{
	float yaw; //y-axis
	float pitch; // x-axis
	float roll; // z-axis
	float PI = 3.14159265358979323846f;

	Quaternion temp;
	temp = *this;

	temp.Normalize();
	
	pitch = atan2f((2.0f * (temp.quaternion.w * temp.quaternion.x + temp.quaternion.y * temp.quaternion.z)), (1.0f - 2.0f * (temp.quaternion.x * temp.quaternion.x + temp.quaternion.y * temp.quaternion.y)) * 180.0f/ PI);
	yaw = asinf(2.0f * (temp.quaternion.w * temp.quaternion.y - temp.quaternion.z * temp.quaternion.x) * 180.0f / PI);
	roll = atan2f((2.0f * (temp.quaternion.w * temp.quaternion.z + temp.quaternion.x * temp.quaternion.y)), (1.0f - 2.0f * (temp.quaternion.y * temp.quaternion.y + temp.quaternion.z * temp.quaternion.z)) * 180.0f / PI);
	
	//return EulerAngles(yaw, pitch, roll);
	return EulerAngles(roll, pitch, yaw);

}
