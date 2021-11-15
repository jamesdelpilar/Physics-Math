#include "Physics.h"
#include <iostream>
#include "VMath.h"

using namespace MATH;

void Physics::ApplyForce(PhysicsObject& object)
{
	object.accel = object.force / object.mass;
}

void Physics::SimpleNewtonMotion(PhysicsObject& object, const float deltaTime) {

	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}


bool Physics::PlaneSphereCollision(const PhysicsObject& object, const Plane& p) {

	// Checks for collision 
	if (VMath::distance(Sphere(object.pos.x, object.pos.y, object.pos.z, object.radius), p) <= object.radius)
	{
		return true;
	}

	if (VMath::distance(Sphere(object.pos.x, object.pos.y, object.pos.z, object.radius), p) > object.radius)
	{
		return false;
	}

}

void Physics::PlaneSphereCollisionResponse(PhysicsObject& object, const Plane& p) {

	if (PlaneSphereCollision(object, p)) {

		// Step 1: Normalize
		Plane planeNormal = p;
		planeNormal.normalize();

		// Step 2: P = (-Vi . N^)N^
		Vec3 P = VMath::dot(-object.vel, planeNormal) * (planeNormal);

		// Step 3: Vi + 2P
		object.vel = object.vel + (2.0f * P);
	}
}

bool Physics::SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject& object2) {

	// Takes the direction of Object 1 & 2 by subtracting and calculating magnitude
	// If it is less than the radius of both objects, collision occurs. 
	// If not, collision has not occurred

	if (VMath::distance(object2.pos, object1.pos) <= (object1.radius + object2.radius)) {
		return true;
	}
	else if (VMath::distance(object2.pos, object1.pos) >= (object1.radius + object2.radius)) {
		return false;
	}
}

void Physics::SphereSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2) { 

	if (SphereSphereCollision(object1, object2))
	{
		// Step 1: B - A
		Vec3 sphereNormal = object2.pos - object1.pos;

		// Step 2 Normalize
		Vec3 sphereNormalized = VMath::normalize(sphereNormal);

		//Step 3 - 5: P = (-Vi . N^)N^ | VF = Vi + 2P

		//Ball A | VF = Vi + 2P
		Vec3 sphereAP = (VMath::dot(-object1.vel, sphereNormalized) * sphereNormalized);
		object1.vel = object1.vel + (2.0f * sphereAP);

		//Ball B
		Vec3 sphereBP = (VMath::dot(-object2.vel, sphereNormalized) * sphereNormalized);
		object2.vel = object2.vel + (2.0f * sphereBP);
	}

}

void Physics::SphereStaticSphereCollisionResponse(PhysicsObject& object1, PhysicsObject& object2)
{
	if (SphereSphereCollision(object1, object2)) {
		// Step 1: B - A
		Vec3 sphereNormal = object2.pos - object1.pos;

		// Step 2 Normalize
		Vec3 sphereNormalized = VMath::normalize(sphereNormal);

		//Step 3 - 5: P = (-Vi . N^)N^ | VF = Vi + 2P

		//Ball | VF = Vi + 2P
		Vec3 sphereAP = (VMath::dot(-object1.vel, sphereNormalized) * sphereNormalized);
		object1.vel = object1.vel + (2.0f * sphereAP);

		/// Adding coefficient of resitution aka elasticity
		//float a1 - ((body.mass-e * body2.mass)*)

	}
}

void Physics::ApplyForces(PhysicsObject& object, float waterHeight)
{
	// Member Variables 
	
	float g = 9.81f; // Earth's Gravitational Acceleration | 9.8f or 9.81f

	float c = 0.5f; // Drag coefficient

	float V = 0.0f;	// Linear Velocity Vector | Submerged Volume of Log | Total Volume

	float p = 5.0f; // Liquid Density

	float l = 1.0f;	// Volume of a full cylinder | V = PI * r^2 * l

	float m = object.pos.y - waterHeight; // Distance(m) | distance from the centre of the circle to the waterline

	float theta = 2.0f * acos( m / object.radius); // Theta | theta = 2cos^-1 (m/r) 

	float r2 = object.radius * object.radius;

	////////////////////////////////
	// Object is FULLY SUBMERGED // 
	//////////////////////////////
	
	//Volume of a Full Cylinder | V = PI * r^2 * l

	if ((object.pos.y + object.radius) <= waterHeight) 
	{
		V = M_PI * r2 * l;
	}

	////////////////////////////////////
	// Object is PARTIALLY SUBMERGED // 
	//////////////////////////////////
	
	// If the waterline is below the cylinder's centre | V = 1/2 * r^2 (theta - sin(theta)) * l

	else if (object.pos.y > waterHeight && (object.pos.y - object.radius) <= waterHeight)
	{
		V = 0.5f * r2 * (theta - sin(theta) * l);
	}

	// If the waterline is above the centre | V = PI * r^2 * l - 1/2 * r^2 (theta - sin(theta)) * l 
	else if (object.pos.y < waterHeight && (object.pos.y + object.radius) >= waterHeight)
	{
		V = (M_PI * r2 * l) - (0.5f * r2 * l * (theta - sin(theta)));
	}

	// Force on the log
	Vec3 FWeight = Vec3(0, (object.mass * -g), 0); 
	Vec3 FDrag = -c * object.vel; 
	Vec3 FBouyancy(0.0f, p * g * V, 0.0f); 

	object.force = FWeight + FDrag + FBouyancy;
	
	// All above WATERHEIGHT POS + RADIUES = VOLUME = 0



}


