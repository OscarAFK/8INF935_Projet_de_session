#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Particle.h"
#include "Physics.h"
#include "Display.h"
#include "Camera.h"

void processInput(GLFWwindow* window, Camera* camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveCamera(cameraSpeed * camera->getCameraFront());
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveCamera(-cameraSpeed * camera->getCameraFront());
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveCamera(-glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveCamera(glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed);
}

int main()
{

	float dt = 0.01f;
	float t = 0;

	float currentTime = clock();
	float accumulator = 0.0;
	

	
	//Initializing physics and display
	Physics physic = Physics();
	
	Display display = Display(&physic);
	
	while (!display.windowShouldClose()) {
		
		processInput(display.getWindow(), display.getCamera());

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

		glfwPollEvents();
	}
	
	display.quitLibraries();

	exit(EXIT_SUCCESS);
}




