#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>
#include "Body.h"


using namespace MATH;
#define NUM_BALLS 3

class Scene1 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	
	Body* planet; // Planet
	Body* star1;  // Star1
	Body* star2; // Star 2
		
	Matrix4 InverseProjectionMatrix;
	Body* ballArray[NUM_BALLS];
	SDL_Renderer* renderer;

public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
};

#endif

