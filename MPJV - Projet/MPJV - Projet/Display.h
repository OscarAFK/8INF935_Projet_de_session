#pragma once

#include "Physics.h"
#include <memory>
#include <GLFW/glfw3.h>

class Display
{
private:
	Physics* m_linkedPhysics;
	int m_sizeX;
	int m_sizeY;
	void drawCircle(float cx, float cy, float r, int num_segments);

public:
	Display() = default;
	Display(Physics* physics, int sizeX, int sizeY);
	~Display() = default;

	void linkToPhysics(Physics* physics);
	void drawPhysics();

};

