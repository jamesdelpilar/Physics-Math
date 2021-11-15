#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene0::Scene0(): sphereDynamic(nullptr), sphereStatic(nullptr) ,meshPtr(nullptr),shaderPtr(nullptr),texturePtr(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	delete sphereDynamic;
	delete sphereStatic;
	delete meshPtr;
	delete texturePtr;
	delete shaderPtr;
}

bool Scene0::OnCreate() {
	
	lightSource = Vec3(0.0f,0.0f,0.0f);
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print();

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr|| shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (texturePtr->LoadImage("textures/steel.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	sphereDynamic = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (sphereDynamic == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}

	sphereStatic = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (sphereDynamic == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}

	sphereDynamic->setPos(Vec3(2.0f, 2.0f, 0.0f)); // 2,2,0
	//sphereDynamic->setModelMatrix(MMath::translate(sphereDynamic->getPos()) * MMath::scale(1.0f, 1.0f, 1.0f));
	sphereDynamic->setRadius(1.12f);

	sphereStatic->setPos(Vec3(3.0f, 4.0f, 0.0f)); // 3,4,0
	//sphereStatic->setModelMatrix(MMath::translate(sphereStatic->getPos()) * MMath::scale(1.0f, 1.0f, 1.0f));
	sphereStatic->setRadius(1.12f);
	sphereStatic->setVel(Vec3(0.0f, -4.0f, 0.0f));
	
	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {

}

void Scene0::Update(const float deltaTime) {

	sphereDynamic->Update(deltaTime);
	sphereStatic->Update(deltaTime);

	Physics::SphereSphereCollisionResponse(*sphereDynamic, *sphereStatic);

	Physics::SimpleNewtonMotion(*sphereDynamic, deltaTime);
	Physics::SimpleNewtonMotion(*sphereStatic, deltaTime);



	//sphereDynamic->setModelMatrix(MMath::translate(sphereDynamic->getPos()));
	//sphereStatic->setModelMatrix(MMath::translate(sphereStatic->getPos()));

	sphereDynamic->setModelMatrix(MMath::translate((sphereDynamic->getPos()))
		* MMath::scale(sphereDynamic->getRadius(), sphereDynamic->getRadius(), sphereDynamic->getRadius()));
	sphereStatic->setModelMatrix(MMath::translate((sphereStatic->getPos()))
		* MMath::scale(sphereStatic->getRadius(), sphereStatic->getRadius(), sphereStatic->getRadius()));

}

void Scene0::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = sphereDynamic->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(sphereDynamic->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(sphereDynamic->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE,viewMatrix);
	glUniform3fv(sphereDynamic->getShader()->getUniformID("lightPos"), 1, lightSource);

	sphereDynamic->Render();
	sphereStatic->Render();
	std::cout << sphereStatic->getVel().x << ", " << sphereStatic->getVel().y << ", " << sphereStatic->getPos().x << ", " << sphereStatic->getPos().y << "\n";

	glUseProgram(0);
}


void Scene0::OnDestroy() {
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (sphereDynamic) delete sphereDynamic, sphereDynamic = nullptr;
	if (sphereStatic) delete sphereStatic, sphereStatic = nullptr;

}
