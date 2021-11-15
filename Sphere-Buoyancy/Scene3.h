#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Plane.h"
#include <SDL.h>
using namespace MATH;

union SDL_Event;
class Physics;
class DemoObject;
class Mesh;
class Shader;
class Texture;

class Scene3 : public Scene {
private:
	//Created
	Plane* rWall;
	DemoObject* sphereDynamic;

	Physics* physics;
	Vec3 lightSource;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent_) override;
};
#endif
