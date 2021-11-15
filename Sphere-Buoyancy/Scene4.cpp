#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene4.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"

Scene4::Scene4(): sphere(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	
	Debug::Info("Scene4: ", __FILE__, __LINE__);
	physics = new Physics(); 
	shaderPtr = new Shader("shaders/phongVert.glsl", "shaders/phongFrag.glsl");
}

Scene4::~Scene4()
{
	delete sphere;
	delete physics;
}

bool Scene4::OnCreate() {

	lightSource = Vec3(0.0f, 0.0f, 0.0f);
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(5.0f, 5.0f, 10.0f), Vec3(5.0f, 5.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
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
	sphere = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (sphere == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}

	// Dynamic Sphere values on start
	sphere->setPos(Vec3(10.0f, 10.0f, 0.0f));
	sphere->setVel(Vec3(0.0f, 0.0f, 0.0f));
	sphere->setMass(1.0f);
	sphere->setRadius(1.0f); 

	return true;
}

void Scene4::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene4::Update(const float deltaTime) {

	// Buoyancy Test
	physics->ApplyForces(*sphere, 0.0f);
	physics->ApplyForce(*sphere);
	physics->SimpleNewtonMotion(*sphere, deltaTime);

	sphere->setModelMatrix(MMath::translate(sphere->getPos()) * MMath::rotate(90.0f, Vec3(1.0f, 0.0f, 0.0f)) * MMath::scale(1.0f, 1.0f, 1.0f));

}

void Scene4::Render() const {
	/// Clear the screen
	glClearColor(0.5f, 0.0f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	GLuint program = sphere->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(sphere->getShader()->getUniformID("lightPos"), 1, lightSource);

	sphere->Render();

	glUseProgram(0);
}


void Scene4::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (sphere) delete sphere, sphere = nullptr;
}
