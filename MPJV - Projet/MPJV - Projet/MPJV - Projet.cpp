#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Time.h"
#include "Shader.h"
#include "Particle.h"
#include "Physics.h"
#include "Display.h"
#include "Camera.h"
#include "Utilitaire/stb_image.h"
#include "Cube.h"
#include "ShapeRenderer.h"
#include "Utilitaire/Rigidbody.h"

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
    Time time = Time();

    std::vector<System*> systems;
    systems.push_back(&physic);
    systems.push_back(&display);
    systems.push_back(&time);


    Shader cubeShader("Shaders/cubeShader.vs", "Shaders/cubeShader.fs");
    Shader lightShader("Shaders/lightShader.vs", "Shaders/lightShader.fs");


    Cube lightCube = Cube(lightPos, glm::vec3(45, 0, 0), glm::vec3(0.25f, 0.25f, 0.25f));
    Cube cube = Cube(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 2, 1));


    std::vector<Entity*> entities;

    Entity e = Entity("CubeTest");
    e.addComponent<ShapeRenderer>();
    e.addComponent<Rigidbody>();
    e.getComponent<Rigidbody>()->Initialize(1,0.9,0.9, tenseursFormesDeBase::Cuboide(1,Vector3D(1,1,1)));
    entities.push_back(&e);


    glEnable(GL_DEPTH_TEST);

    // inputs
    glfwSetFramebufferSizeCallback(display.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(display.getWindow(), mouse_callback);
    glfwSetScrollCallback(display.getWindow(), scroll_callback);    

    // tell GLFW to capture our mouse
    glfwSetInputMode(display.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);


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

		while (accumulator >= dt) //-> mettre ca dans le physics
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

        for (size_t i = 0; i < systems.size(); i++)
        {
            systems[i]->tick(entities);
        }

		display.renderUI(entities); // MOVE THIS INSIDE display.tick(entities);

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
        float yoffset = lastY - ypos;

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




