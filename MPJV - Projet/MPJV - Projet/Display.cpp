#include "Display.h"
#include <iostream>

#pragma region Constructors

Display::Display(Physics* physics) : m_linkedPhysics(physics)
{
}

#pragma endregion


#pragma region Mutex

void Display::linkToPhysics(Physics *physics)
{
	m_linkedPhysics = physics;
}

#pragma endregion


#pragma region Methods

void Display::drawPhysics()
{
	auto listOfParticles = m_linkedPhysics->getAllParticle();
	
	for (std::map<int, Particle>::iterator it = (*listOfParticles).begin(); it != (*listOfParticles).end(); ++it) {
		drawCircle(it->second.getPosition().getX(), it->second.getPosition().getY(), 0.02, 4);
	}
}

void Display::drawCircle(float cx, float cy, float r, int num_segments)		//Fonction récupérée sur stackOverflow à cette adresse: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

#pragma endregion