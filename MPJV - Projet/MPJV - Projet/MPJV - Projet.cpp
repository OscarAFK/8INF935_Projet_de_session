#include <stdio.h>
#include <iostream>
#include "Particle.h"
#include "Physics.h"
#include <GLFW/glfw3.h>

int main()
{
    float deltaTime = 0.01f;
    
    //GLFW initialization
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(480, 480, "OpenGL Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //Tests physics
    Physics physic = Physics();
    physic.addParticle(0, 1, Vector3D(1, 2, 3), Vector3D(1, 2, 3), Vector3D(1, 2, 3));
    std::cout << physic.getParticle(0)->to_string() << std::endl;
    physic.update(1);
    std::cout << physic.getParticle(0)->to_string() << std::endl;
    physic.removeParticle(0);

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		
        
        //Swap buffer and check for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glfwDestroyWindow(window);
    glfwTerminate;
    exit(EXIT_SUCCESS);

    /*
    bool run = true;
    while (run)
    {
        p2.integrate(deltaTime);
        std::cout << p2.to_string() << std::endl;
        //printf(position.to_string().c_str());*

    }*/
}



