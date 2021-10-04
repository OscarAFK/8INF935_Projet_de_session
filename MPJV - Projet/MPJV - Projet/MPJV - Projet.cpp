#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>

#include "Particle.h"
#include "Physics.h"
#include "Display.h"

#include "ParticleForceGenerators/ParticleGravity.h"

#define WINDOW_SIZE_X	480
#define WINDOW_SIZE_Y	480

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void ShootProjectile(Physics* physic, int choiceIndex)
{
	Particle particle;
	std::vector<ParticleForceGenerator*> generators;
	ParticleGravity gravity = ParticleGravity();

	switch (choiceIndex) {
	case 1:
		std::cout << "vous avez choisi le boulet de canon" << std::endl;
		particle = Particle(0.01f, 1, Vector3D(0, 0, 0), Vector3D(0, 20, 0), Vector3D(0, 0, 0));
		gravity = ParticleGravity();
		generators.push_back(&gravity);
		break;

	case 2:
		std::cout << "vous avez choisi la boule de feu" << std::endl;
		particle = Particle(0.05f, 1, Vector3D(0, 0, 0), Vector3D(1, 2, 1), Vector3D(0, 0, 0));
		gravity = ParticleGravity(-5);
		generators.push_back(&gravity);
		break;

	case 3:
		std::cout << "vous avez choisi le laser" << std::endl;
		particle = Particle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0));
		break;

	case 4:
		std::cout << "vous avez choisi la balle" << std::endl;
		particle = Particle(0.99f, 1, Vector3D(0, 0, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0));
		gravity = ParticleGravity();
		generators.push_back(&gravity);
		break;

	default:
		return;
	}
	physic->addParticle(std::move(particle), generators);
}


int main()
{   
	//GLFW initialization
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "OpenGL Example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}

	//Initializing physics and display
	Physics physic = Physics();
	/*std::cout << "Bienvenue au stand de tir\nVeuillez choisir votre projectile.\n1 : Boulet de canon\n2 : Boule de feu\n3 : Laser\n4 : Balle\n5 : Projectile modifiable\nLes vecteurs sont au format(x,y,z)" << std::endl;
	int choice;
	std::cin >> choice;
	

	}*/
	Display display = Display(&physic, WINDOW_SIZE_X, WINDOW_SIZE_Y);

	#pragma region ImGui Setup
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
#pragma endregion

	std::string vertexShader =
		"#version 330\n"\
		"layout(location=0) in vec4 position;\n"\
		"void main(void)\n"\
		"{\n"\
		"   gl_Position = position;\n"\
		"}\n";

	std::string FragmentShader =
		"#version 330\n"\
		"layout(location=0)out vec4 color;\n"\
		"void main(void)\n"\
		"{\n"\
		"   color = vec4(1.0, 1.0, 1.0, 1.0);\n"\
		"}\n";

	unsigned int shader = CreateShader(vertexShader, FragmentShader);
	glUseProgram(shader);

	std::map<std::string, int> projectileMap1 = {
		//Le -10 dans l'accélération représente la gravité
	{ "Boulet de Canon", 1 },
	{ "Boule de feu", 2 },
	{ "Laser", 3},
	{ "Balle", 4}
	};
	
	std::map<std::string, Particle> projectileMap = {
		//Le -10 dans l'accélération représente la gravité
	{ "Boulet de Canon", Particle(0.01f, 1, Vector3D(0, 0, 0), Vector3D(40, 10, 0), Vector3D(0, -10, 0)) },
	{ "Boule de feu", Particle(0.05f, 1, Vector3D(0, 0, 0), Vector3D(20, 40, 0), Vector3D(0, -10, 0)) },
	{ "Laser", Particle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0))},
	{ "Balle", Particle(0.99f, 1, Vector3D(0, 0, 0), Vector3D(80, 80, 0), Vector3D(0, -10, 0))}
	};
	static _int64 selected = -1;
	char projectileName[64] = "";

	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		//Render Physics
		glClear(GL_COLOR_BUFFER_BIT);
		

		//RENDER PHYSICS

		//Update physics and rendering
		physic.update();
		//std::cout << physic.getParticle(0)->to_string() << std::endl;
		display.drawPhysics();


		//RENDER UI

		//Create new ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Stand de tir");
		ImGui::Text("Bienvenue au stand de tir\n");
		ImGui::Text("Veuillez choisir votre projectile.\n");
		
		if (ImGui::TreeNode("Liste des projectiles"))
		{
			for (std::map<std::string, Particle>::iterator it = projectileMap.begin(); it != projectileMap.end(); ++it) {
				if (ImGui::Selectable(it->first.c_str(), selected == std::distance(projectileMap.begin(), it))) {
					selected = std::distance(projectileMap.begin(), it);
					sprintf_s(projectileName, "%s", it->first.c_str());
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::Button("Shoot"))
		{
			if (selected != -1)
			{
				//ShootProjectile(&physic, selected + 1);
				Particle particle;
				std::vector<ParticleForceGenerator*> generators;
				ParticleGravity gravity = ParticleGravity();

				switch (selected + 1) {
				case 1:
					std::cout << "vous avez choisi le boulet de canon" << std::endl;
					particle = Particle(0.01f, 1, Vector3D(0, 0, 0), Vector3D(0, 20, 0), Vector3D(0, 0, 0));
					gravity = ParticleGravity();
					generators.push_back(&gravity);
					break;

				case 2:
					std::cout << "vous avez choisi la boule de feu" << std::endl;
					particle = Particle(0.05f, 1, Vector3D(0, 0, 0), Vector3D(1, 2, 1), Vector3D(0, 0, 0));
					gravity = ParticleGravity(-5);
					generators.push_back(&gravity);
					break;

				case 3:
					std::cout << "vous avez choisi le laser" << std::endl;
					particle = Particle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0));
					break;

				case 4:
					std::cout << "vous avez choisi la balle" << std::endl;
					particle = Particle(0.99f, 1, Vector3D(0, 0, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0));
					gravity = ParticleGravity();
					generators.push_back(&gravity);
					break;

				default:
					break;
				}
				physic.addParticle(std::move(particle), generators);
			}
		}
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		

		//Swap buffer and check for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glDeleteProgram(shader);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}




