#ifndef PHYSICS_H
#define PHYSICS_H
#include "PhysicsObject.h"
#include "Plane.h"
#include "Sphere.h"
#include "Matrix.h"
class Physics {
public:
	static void ApplyForce(PhysicsObject& object);
	static void SimpleNewtonMotion(PhysicsObject& object, const float deltaTime);
	static bool PlaneSphereCollision(const PhysicsObject& object, const Plane& p);
	static void PlaneSphereCollisionResponse(PhysicsObject& object, const Plane& p);
	static bool SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2);
	static void SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2);
	static void SphereStaticSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2); // Added
	static void ApplyForces(PhysicsObject& object, float waterHeight); // Added 
	


};

#endif

