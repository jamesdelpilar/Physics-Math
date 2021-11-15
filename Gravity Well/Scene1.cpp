#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "VMath.h"
#include "Body.h"

Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;

	planet = new Body(Vec3(10.0f, 20.0f, 0.0f), Vec3(-2.5f, 3.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	star1 = new Body(Vec3(5.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 100.0f);
	star2 = new Body(Vec3(15.0f, 25.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 150.0f);
	
}

Scene1::~Scene1(){
	delete planet;
	delete star1;
	delete star2;
}

bool Scene1::OnCreate() {
	int w, h;
	float xAxis = 60.0f; //30
	float yAxis = 30.0f; //15
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	IMG_Init(IMG_INIT_PNG);									
	SDL_Surface* planetImage = IMG_Load("earth1.png");
	SDL_Surface* star1Image = IMG_Load("star1.png");
	SDL_Surface* star2Image = IMG_Load("star1.png");

	if (planetImage == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else {
		planet->setImage(planetImage);
		star1->setImage(star1Image);
		star2->setImage(star2Image);
		Vec3 worldCoordsFromScreenCoords;
		worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(planetImage->w);
		worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(planetImage->h);
		worldCoordsFromScreenCoords.print();
		planet->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		star1->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
	}

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	float star1mass = 100.0f;
	float star2mass = 150.0f;
	float planetmass = 1.0f;
	float G = 1.0f;

//Star1

//Step 1: Direction Vector from Planet to Star1

	Vec3 Star1Direction = star1->getPos() - planet->getPos(); 

//Step 2: Distance from the Planet to the Star
	float Star1r1 = VMath::distance(star1->getPos(), planet->getPos());

	//float Star1r1 = sqrt(pow(Star1Direction.x, 2) + pow(Star1Direction.y, 2));

//Step 3: Magnitude of the Force Vector = G * Mplanet1 * Mstar1 / r^2
	float Star1MagnitudeFg = star1mass / pow(Star1r1, 2);

//Step 4: Normalize the Star

	Star1Direction = VMath::normalize(Star1Direction);

//Step 5: Force of Gravity of Star 

	Vec3 ResultStar1 = Star1MagnitudeFg * Star1Direction;

//Star2 (Repeat Star 1 Steps)

	Vec3 Star2Direction = star2->getPos() - planet->getPos(); 

	float Star2r1 = VMath::distance(star2->getPos(), planet->getPos());

	//float Star2r1 = sqrt(pow(Star2Direction.x, 2) + pow(Star2Direction.y, 2));

	float Star2MagnitudeFg = star2mass / pow(Star2r1, 2);

	Star2Direction = VMath::normalize(Star2Direction);

	Vec3 ResultStar2 = Star2MagnitudeFg * Star2Direction;

// Net Force of Gravity

	Vec3 NetForceStar = ResultStar1 + ResultStar2;

		planet->ApplyForce(NetForceStar);
		planet->Update(deltaTime);

}

void Scene1::Render() {
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	Vec3 screenCoords;
	SDL_Rect square;

	screenCoords = projectionMatrix * star1->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = star1->getImage()->w;
	square.h = star1->getImage()->h;
	SDL_BlitSurface(star1->getImage(), nullptr, screenSurface, &square);


	screenCoords = projectionMatrix * star2->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = star2->getImage()->w;
	square.h = star2->getImage()->h;
	SDL_BlitSurface(star2->getImage(), nullptr, screenSurface, &square);

	screenCoords = projectionMatrix * planet->getPos();
	square.x = static_cast<int>(screenCoords.x);
	square.y = static_cast<int>(screenCoords.y);
	square.w = planet->getImage()->w;
	square.h = planet->getImage()->h;
	SDL_BlitSurface(planet->getImage(), nullptr, screenSurface, &square);

	SDL_UpdateWindowSurface(window);

}