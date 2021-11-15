#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene1.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"
#include "Timer.h"

Scene1::Scene1() : sphereDynamic(nullptr), sphereStatic(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr)
{
	lightSource = Vec3(0.0f, 0.0f, 0.0f);
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(7.0f, 0.0f, 10.0f), Vec3(7.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print();
	physics = new Physics();
	ObjLoader::loadOBJ("meshes/Sphere.obj");
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	texturePtr = new Texture();
	texturePtr->LoadImage("textures/steel.jpg");

	//Creating New Objects
	sphereDynamic = new DemoObject(meshPtr, shaderPtr, texturePtr);
	sphereStatic = new DemoObject(meshPtr, shaderPtr, texturePtr);

	Debug::Info("Created Scene1", __FILE__, __LINE__);
}

Scene1::~Scene1()
{
	delete sphereDynamic; delete sphereStatic; delete physics; delete meshPtr; delete texturePtr; delete shaderPtr;
}

bool Scene1::OnCreate() {
	//Dynamic Sphere Values

	sphereDynamic->setPos(Vec3(2.0f, 2.0f, 0.0f)); // Assigned Position = (2,2,0)
	sphereDynamic->setRadius(1.12f);
	sphereDynamic->setVel(Vec3(0.0f, -4.0f, 0.0f));

	//Static Sphere Values
	sphereStatic->setPos(Vec3(3.0f, 4.0f, 0.0f)); // Assigned Position = (3,4,0)
	sphereStatic->setVel(Vec3(0.0f, 4.0f, 0.0f));
	sphereStatic->setRadius(1.12f);

	//Test Positions

	sphereDynamic->setPos(Vec3(5.0f, 5.0f, 0.0f));
	sphereStatic->setPos(Vec3(3.0f, -5.0f, 0.0f));

	return true;
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene1::Update(const float deltaTime) {
	physics->SphereSphereCollisionResponse(*sphereDynamic, *sphereStatic);

	physics->SimpleNewtonMotion(*sphereDynamic, deltaTime);
	physics->SimpleNewtonMotion(*sphereStatic, deltaTime);

	sphereDynamic->setModelMatrix(MMath::translate((sphereDynamic->getPos())) * MMath::scale(sphereDynamic->getRadius(), sphereDynamic->getRadius(), sphereDynamic->getRadius()));
	sphereStatic->setModelMatrix(MMath::translate((sphereStatic->getPos())) * MMath::scale(sphereStatic->getRadius(), sphereStatic->getRadius(), sphereStatic->getRadius()));

}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
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

	//Rendering
	sphereDynamic->Render();
	sphereStatic->Render();

	glUseProgram(0);
}


void Scene1::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (sphereDynamic) delete sphereDynamic, sphereDynamic = nullptr;
}
