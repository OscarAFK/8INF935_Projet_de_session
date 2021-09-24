#pragma once

#include "Physics.h"
#include <memory>
#include <GLFW/glfw3.h>

class Display
{
private:
	Physics* m_linkedPhysics;

	void drawCircle(float cx, float cy, float r, int num_segments);

public:
	Display() = default;
	Display(Physics* physics);
	~Display() = default;

	void linkToPhysics(Physics* physics);
	void drawPhysics();

};

