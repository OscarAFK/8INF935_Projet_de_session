#pragma once

#include "Physics.h"
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Camera.h"
#include "Cube.h"
#include "System.h"

class Display : public System
{
private:

	//attribute used with the display libraries
	GLFWwindow* window;
	Camera* m_camera;
	ImGuiContext* GImGui;

	//Other variables
	std::vector<std::string> projectileMap;
	_int64 selected;
	char projectileName[64];
	Physics* m_linkedPhysics;
	unsigned int m_cubeVAO = -1;
	Shader* m_lightShader;
	Shader* m_cubeShader;

	bool demoWindowOpened = true;
	bool sceneWindowOpened = true;
	bool debugWindowOpened = false;
	bool helpWindowOpened = false;

	//Methods
	void drawCircle(float cx, float cy, float r, int num_segments);
	void drawSquare(float cx, float cy, float d);

public:
	Display() = default;
	Display(int windowSizeX, int windowSizeY, Physics* physics, Camera* camera);
	~Display() = default;

	void linkToPhysics(Physics* physics);
	void setCamera(Camera* camera);
	void drawPhysics();
	void drawIntermediatePhysics(const float alpha);
	void initDisplayLib(int windowSizeX, int windowSizeY);
	GLFWwindow* getWindow();
	Camera* getCamera();
	const bool windowShouldClose();
	void setupView();
	void renderUI(std::vector<Entity*> entities);
	void shootProjectile(int projectileId);
	void swapBuffers();
	void quitLibraries();
	void terminalCommand();
	void tick(std::vector<Entity*> entities) override;
	void createCubeVAO();
	unsigned int getCubeVAO();
	void showDemoWindow(bool* p_open);
	void showSceneWindow(bool* p_open, std::vector<Entity*> entities);
	void showDebugWindow(bool* p_open);
	void showHelpWindow(bool* p_open);
};

