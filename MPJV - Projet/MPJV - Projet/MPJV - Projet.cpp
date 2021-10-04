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
	/*std::cout << "Bienvenue au stand de tir\nVeuillez choisir votre projectile.\n1 : Boulet de canon\n2 : Boule de feu\n3 : Laser\n4 : Balle\n5 : Projectile modifiable\nLes vecteurs sont au format(x,y,z)" << std::endl;
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1: std::cout << "vous avez choisi le boulet de canon" << std::endl;
		physic.addParticle(0.01, 1, Vector3D(0, 0, 0), Vector3D(1, -5, 3), Vector3D(0, 0, 0));
		break;
	case 2: std::cout << "vous avez choisi la boule de feu" << std::endl;
		physic.addParticle(0.05, 1, Vector3D(0, 0, 0), Vector3D(1, 2, 1), Vector3D(0, 0, 0));
		break;
	case 3: std::cout << "vous avez choisi le laser" << std::endl;
		physic.addParticle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0));
		break;
	case 4: std::cout << "vous avez choisi la balle" << std::endl;
		physic.addParticle(0.99, 1, Vector3D(0, 0, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0));
		break;
	case 5: std::cout << "vous avez choisi le projectile personnel" << std::endl;
		break;
	default:
		return;

	}*/
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




