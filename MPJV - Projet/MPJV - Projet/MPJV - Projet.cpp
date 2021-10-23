#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>


#include "Particle.h"
#include "Physics.h"
#include "Display.h"


int main()
{

	float dt = 0.01f;
	float t = 0;

	float currentTime = clock();
	float accumulator = 0.0;
	

	
	//Initializing physics and display
	Physics physic = Physics();
	
	Display display = Display(&physic);

	display.initDisplayLib();
	
	while (!display.windowShouldClose()) {
		
		display.setupView();
		

		//RENDER PHYSICS
		float newTime = clock();
		float frameTime = (newTime - currentTime) / CLOCKS_PER_SEC;
		if (frameTime > 0.25)
			frameTime = 0.25;
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= dt)
		{
			
			//Update physics
			physic.update(t, dt);
			t += dt;
			accumulator -= dt;
		}

		const float alpha = accumulator / dt;

		display.drawIntermediatePhysics(alpha);
		
		display.renderUI();

		display.swapBuffers();
	}
	
	display.quitLibraries();

	exit(EXIT_SUCCESS);
}




