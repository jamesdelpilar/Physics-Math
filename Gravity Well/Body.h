#ifndef BODY_H
#define BODY_H

#include "Vector.h"
#include <SDL_image.h>
using namespace MATH;

class Body {
public:
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;
	float mass;
	float birdtotalTime;
	Vec3 gravityForce;
	
	SDL_Surface* image;
	Vec3 imageSizeWorldCoords;

	bool captured;

public:
	Body(); /// zero arg constructor
	Body(Vec3 pos_, Vec3 vel_, Vec3 acc_, float mass_);

	~Body();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);
	void ApplyForce(Vec3 force_);

	Vec3 getPos() { return pos; }
	void setPos(Vec3 pos_) { pos = pos_; }
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }


	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) { imageSizeWorldCoords = imageSizeWorldCoords_; }
	Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords;}

	bool isGrabbed() { return captured; }
	void grabbed() { captured = true; }
	void letGo() { captured = false; }


};

#endif
