#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Shader.h"
#include "Particle.h"
#include "Physics.h"
#include "Display.h"
#include "Camera.h"
#include "Utilitaire/stb_image.h"
#include "Cube.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMousePress = true;
bool firstMouseRelease = true;

float dt = 0.01f;
float t = 0;
Display display;

int main()
{
	float currentTime = clock();
	float accumulator = 0.0;
	

	
	//Initializing physics and display
	Physics physic = Physics();
	
	display = Display(&physic, &camera);

	//============================================================================================

    // inputs
    glfwSetFramebufferSizeCallback(display.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(display.getWindow(), mouse_callback);
    glfwSetScrollCallback(display.getWindow(), scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(display.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    Cube cube1 = Cube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    Cube cube2 = Cube(glm::vec3(0, 5, 0), glm::vec3(2, 3, 1));

	//==============================================================================================

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
		

		//====================================================================================

        // input
        // -----
        processInput(display.getWindow());

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cube1.render(&display);
        cube2.render(&display);

		//====================================================================================

		display.renderUI();

		display.swapBuffers();

		glfwPollEvents();
	}
	
	display.quitLibraries();

	exit(EXIT_SUCCESS);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (firstMousePress)
        {
            lastX = xpos;
            lastY = ypos;
            firstMousePress = false;
            firstMouseRelease = true;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        if (firstMouseRelease)
        {
            firstMouseRelease = false;
            firstMousePress = true;
        }
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}




