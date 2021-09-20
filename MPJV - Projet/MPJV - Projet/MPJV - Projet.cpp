#include <stdio.h>
#include <iostream>
#include "Particle.h"
#include <GLFW/glfw3.h>

int main()
{
    float deltaTime = 0.01f;

    std::string input;
    Particle p1 = Particle();
    Particle p2 = Particle(0, 1, Vector3D(1,2,3), Vector3D(1, 2, 3), Vector3D(1, 2, 3));

    std::cout << p1.to_string() << std::endl;
    std::cout << p2.to_string() << std::endl;
    
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



