#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	ball1 = new Body(Vec3(3.0f,12.5f,0.0f), Vec3(10.0f,0.0f,0.0f), Vec3(0.0f, -9.8f, 0.0f), 1.0f);
	ball2 = new Body(Vec3(20.0f,12.0f,0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec3(0.0f,-9.8f, 0.0f), 1.0f);
}

Scene0::~Scene0(){
	delete ball1;
	delete ball2;
}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	float xAxis = 30.0f;
	float yAxis = 15.0f;


	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* ballImage = IMG_Load("ball.png");
	
	if(ballImage == nullptr){
		std::cerr << "Can't open the image" << std::endl;
		return false;
	} else {
		ball1->setImage(ballImage);
		ball2->setImage(ballImage);
		Vec3 worldCoordsFromScreenCoords;
		worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(ballImage->w);
		worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(ballImage->h);

		
		worldCoordsFromScreenCoords.print();
		ball1->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		ball2->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
	}
	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	ball1->Update(deltaTime);
	ball2->Update(deltaTime);
}

void Scene0::Render() {
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	Vec3 screenCoords;
	SDL_Rect square;

	

	screenCoords = projectionMatrix * ball2->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = ball2->getImage()->w;
	square.h = ball2->getImage()->h;
	SDL_BlitSurface(ball2->getImage(), nullptr, screenSurface, &square);

	screenCoords = projectionMatrix * ball1->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = ball1->getImage()->w;
	square.h = ball1->getImage()->h;
	SDL_BlitSurface(ball1->getImage(), nullptr, screenSurface, &square);

	SDL_UpdateWindowSurface(window);
}