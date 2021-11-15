#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include <SDL.h>
using namespace MATH;

union SDL_Event;
class Physics;
class DemoObject;
class Mesh;
class Shader;
class Texture;

class Scene1 : public Scene{
private:
	//Created Objects
	DemoObject* sphereDynamic;
	DemoObject* sphereStatic;

	Physics* physics;
	Vec3 lightSource;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent_) override;
};
#endif
