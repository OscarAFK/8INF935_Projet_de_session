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

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float lastX = WINDOW_SIZE_X / 2.0f;
float lastY = WINDOW_SIZE_Y / 2.0f;
bool firstMousePress = true;
bool firstMouseRelease = true;

float dt = 0.01f;
float t = 0;

int main()
{
	float currentTime = clock();
	float accumulator = 0.0;
	
    //Initializing physics and display
    Physics physic = Physics();
    Display display = Display(WINDOW_SIZE_X , WINDOW_SIZE_Y ,&physic, &camera);

    // inputs
    glfwSetFramebufferSizeCallback(display.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(display.getWindow(), mouse_callback);
    glfwSetScrollCallback(display.getWindow(), scroll_callback);

    glEnable(GL_DEPTH_TEST);

    // tell GLFW to capture our mouse
    glfwSetInputMode(display.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    Shader cubeShader("Shaders/cubeShader.vs", "Shaders/cubeShader.fs");
    Shader lightShader("Shaders/lightShader.vs", "Shaders/lightShader.fs");

    Cube lightCube = Cube(lightPos, glm::vec3(0.25f, 0.25f, 0.25f), &lightShader);
    Cube cube = Cube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), &cubeShader);

	while (!display.windowShouldClose()) {

		display.setupView();

        //Inputs
        processInput(display.getWindow());
		
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
		
        //Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.use();
        cubeShader.setVec3("light.position", lightPos);
        cubeShader.setVec3("viewPos", camera.Position);

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        cubeShader.setVec3("light.ambient", ambientColor);
        cubeShader.setVec3("light.diffuse", diffuseColor);
        cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        cubeShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        cubeShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
        cubeShader.setFloat("material.shininess", 32.0f);


        cube.render(&display);
        lightCube.render(&display);


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




