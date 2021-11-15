#include <iostream>
#include "Vec3.h"
#include "Vec4.h"
#include "Ray.h"
#include "Plane.h"

using namespace std;
Plane::Plane() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}
Plane::~Plane()
{
}
Plane::Plane(float x_, float y_, float z_, float d_) {
	plane.x = x_; 
	plane.y = y_; 
	plane.z = z_; 
	plane.w = d_;
}
Plane::Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2) {
	Vec3 e1; 
	Vec3 e2; 
	Vec3 n;
	e1 = v1 - v0;
	e2 = v2 - v1;


	n = e1.Cross(e2);
	n.Normalize();
	float d = -1.0f * ((n.x * v0.x) + (n.y * v0.y) + (n.z * v0.z));
	plane = Vec4(n.x, n.y, n.z, d);
}
Vec3 Plane::intersectionPoint(Ray ray) {

	float t;
	Vec4 L = plane;
	Vec4 S(ray.start.x, ray.start.y, ray.start.z, 1.0f);
	Vec3 V = ray.dir;
	Vec3 N(plane.x, plane.y, plane.z);
	
	float verySmall = 1.0e-7f;

	float NV = N.Dot(V);
	float LS = L.Dot(S);
	



	//2 CASES 
	// If NV = 0 | NO INTERSECTION
    // If LS = 0 | INFNITY
	
	if (abs(NV) < verySmall) 
	{

		if (abs(LS) < verySmall) 
		{
			cout << "INFINITY" << endl;
			return Vec3(-999, -999, -999);
		}

		cout << "NO INTERSECTION" << endl;
		return Vec3(NAN, NAN, NAN);
	}

	else if (t = -1.0f * (LS / NV)) {
		return ray.currentPosition(t);

	}

	

	
}