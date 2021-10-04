#include "Display.h"
#include <iostream>

#pragma region Constructors

Display::Display(Physics* physics, int sizeX, int sizeY) : m_linkedPhysics(physics), m_sizeX(sizeX), m_sizeY(sizeY)
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
	
	for (std::vector<Particle>::iterator it = listOfParticles->begin(); it != listOfParticles->end(); ++it) {
		drawCircle(it->getPosition().getX(), it->getPosition().getY(), 10, 4);
	}
}

void Display::drawIntermediatePhysics(const float alpha)
{
	auto listOfParticles = m_linkedPhysics->getIntermediateParticle(alpha);

	for (std::vector<Particle>::iterator it = listOfParticles->begin(); it != listOfParticles->end(); ++it) {
		drawCircle(it->getPosition().getX(), it->getPosition().getY(), 10, 4);
	}
}

void Display::drawCircle(float cx, float cy, float r, int num_segments)		//Fonction récupérée sur stackOverflow à cette adresse: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f((x + cx)/(float)m_sizeX, (y + cy) / (float)m_sizeY);//output vertex 
	}
	glEnd();
}

#pragma endregion