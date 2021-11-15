#include "Body.h"

Body::Body(){
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	acc.x = 0.0f;
	acc.y = 0.0f;
	acc.z = 0.0f;

	mass = 1.0f;

	

	image = nullptr;
}

Body::Body(Vec3 pos_, Vec3 vel_, Vec3 acc_, float mass_){
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	acc.x = acc_.x;
	acc.y = acc_.y;
	acc.z = acc_.z;
	mass = mass_;

	image = nullptr;
	
}

Body::~Body(){

}

void Body::Update(float deltaTime){

	pos.x += vel.x * deltaTime + 0.5f * acc.x * deltaTime * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * acc.y * deltaTime * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * acc.z * deltaTime * deltaTime;

	vel.x += acc.x * deltaTime;
	vel.y += acc.y * deltaTime;
	vel.z += acc.z * deltaTime;
}

void Body::ApplyForce(Vec3 force_) {
	acc.x = force_.x / mass;
	acc.y = force_.y / mass;
	acc.z = force_.z / mass;
}
