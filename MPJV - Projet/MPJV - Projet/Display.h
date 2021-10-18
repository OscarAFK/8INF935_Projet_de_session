#pragma once

#include "Physics.h"
#include <memory>
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Display
{
private:

	//attribute used with the display libraries
	GLFWwindow* window;
	unsigned int shader;

	//Other variables
	std::vector<std::string> projectileMap;
	_int64 selected;
	char projectileName[64];
	Physics* m_linkedPhysics;

	//Methods
	void drawCircle(float cx, float cy, float r, int num_segments);

public:
	Display() = default;
	Display(Physics* physics);
	~Display() = default;

	void linkToPhysics(Physics* physics);
	void drawPhysics();
	void drawIntermediatePhysics(const float alpha);
	void initDisplayLib();
	GLFWwindow* getWindow();
	const bool windowShouldClose();
	void setupView();
	void renderUI();
	void shootProjectile(int projectileId);
	void swapBuffers();
	void quitLibraries();
	void terminalCommand();

};

