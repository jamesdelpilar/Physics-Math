#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene3.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"

Scene3::Scene3(): sphereDynamic(nullptr), rWall(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	
	Debug::Info("Scene3: ", __FILE__, __LINE__);
	physics = new Physics(); 
	shaderPtr = new Shader("shaders/phongVert.glsl", "shaders/phongFrag.glsl");
}

Scene3::~Scene3()
{
	delete sphereDynamic;
	delete rWall;
	delete physics;
}

bool Scene3::OnCreate() {

	lightSource = Vec3(0.0f, 0.0f, 0.0f);
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(7.0f, 0.0f, 10.0f), Vec3(7.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print();

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		Debug::FatalError("Couldn't load mesh", __FILE__, __LINE__);
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	texturePtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (texturePtr->LoadImage("textures/steel.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	// Creating Objects
	sphereDynamic = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (sphereDynamic == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}

	// Dynamic Sphere values on start
	sphereDynamic->setPos(Vec3(12.0f, 0.0f, 0.0f));
	sphereDynamic->setVel(Vec3(2.0f, 2.0f, 0.0f));

	// Plane Values
	rWall = new Plane(-1.0f, 0.0f, 0.0f, -15.15f);

	return true;
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene3::Update(const float deltaTime) {

	physics->PlaneSphereCollisionResponse(*sphereDynamic, *rWall);
	physics->SimpleNewtonMotion(*sphereDynamic, deltaTime);


	sphereDynamic->setModelMatrix(MMath::translate((sphereDynamic->getPos())) * MMath::scale(sphereDynamic->getRadius(), sphereDynamic->getRadius(), sphereDynamic->getRadius()));
}

void Scene3::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	GLuint program = sphereDynamic->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(sphereDynamic->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(sphereDynamic->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(sphereDynamic->getShader()->getUniformID("lightPos"), 1, lightSource);

	sphereDynamic->Render();

	glUseProgram(0);
}


void Scene3::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (sphereDynamic) delete sphereDynamic, sphereDynamic = nullptr;
}
