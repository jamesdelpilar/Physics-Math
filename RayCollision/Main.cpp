#include <iostream>
#include "AAB.h"
#include "Collider.h"
#include "Mat3.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vec3.h"
#include "Vec4.h"

using std::cout;

int main()
{	
	// Ray-Sphere Collision Test

	// Starting Point
	Vec3 start(2.0f, -1.0f, -1.0f);

	//Direction 
	Vec3 dir(0.0f, 2.0f, 3.0f);

	Ray ray(start, dir);

	Vec3 position(0, 0, 0);
	float radius = 5.0f;
	Sphere sphere(position, radius);
	
	Vec3 collisionPoint = Collider::RaySphereCollisionPoint(ray, sphere);
		cout << "The closest collision point for Ray-Sphere Collistion Test = (" << collisionPoint.x << "," << collisionPoint.y << "," << collisionPoint.z << ")" << endl;
	

	// Ray-AAB Collision Test

	AAB box = AAB(20.0f, 10.0f, 10.0f);

	Vec3 boxIntersection = Collider::RayAABCollisionPoint(ray, box);
		cout << "Closest Intersection Point for Ray-AAB collision test = (" << boxIntersection.x << ", " << boxIntersection.y << ", " << boxIntersection.z << ")" << endl;
	
	return 0;
}