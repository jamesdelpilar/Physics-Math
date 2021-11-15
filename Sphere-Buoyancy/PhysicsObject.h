#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "Vector.h"
#include "Matrix.h"
#include "Sphere.h"

using namespace MATH;

class PhysicsObject {
	friend class Physics;
protected:
	Vec3 pos, vel, accel;
	Vec3 force;
	float mass;
	float radius;
	Sphere boundingSphere;
	float angle, angularVel, angularAccel, rotationalI, torque;
public:
	PhysicsObject();
	virtual ~PhysicsObject();

public:
	/// Untility functions so small they cane be inlined
	inline void setPos(const Vec3 &pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; }
	inline void setVel(const Vec3 &vel_) { vel = vel_; }
	inline Vec3 getVel() { return vel; }
	inline void setAccel(const Vec3 &accel_) { accel = accel_; }
	inline Vec3 getAccel() { return accel; }
	inline void setAngularVel(const float angularVel_) { angularVel = angularVel_; }
	inline float getAngularAccel() { return angularAccel; }
	inline float getAngularVel() { return angularVel; }
	inline float getAngle() { return angle; }
	inline void setAngle(const float angle_) { angle = angle_; }
	inline void setMass(const float mass_) { mass = mass_; }
	inline void setRotationalI(const float rotationalI_) { rotationalI = rotationalI_; }
	inline void setTorque(const float torque_) { torque = torque_; }
	inline float getTorque() { return torque; }
	inline void setForce(Vec3 thrust_) { force = thrust_; }
	inline Vec3 getForce() { return force; }
	inline void setRadius(const float radius_) { radius = radius_; }
	inline float getRadius() { return radius; }
};
#endif

