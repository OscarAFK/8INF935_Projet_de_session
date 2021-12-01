#include "Display.h"
#include <map>
#include "ShapeRenderer.h"


#pragma region Constructors

Display::Display(int windowSizeX, int windowSizeY, Physics* physics, Camera* camera) : m_linkedPhysics(physics), m_camera(camera)
{	
	initDisplayLib(windowSizeX, windowSizeY);
}

#pragma endregion

#pragma region Mutex

void Display::linkToPhysics(Physics *physics)
{
	m_linkedPhysics = physics;
}

void Display::setCamera(Camera* camera)
{
	m_camera = camera;
}

#pragma endregion

#pragma region Methods Class

void Display::drawPhysics()
{
	auto listOfParticles = m_linkedPhysics->getAllParticle();
	auto listOfRigidbody = m_linkedPhysics->getAllRigidbody();
	
	for (std::vector<Particle>::iterator it = listOfParticles->begin(); it != listOfParticles->end(); ++it) {
		//drawCircle(*it->getPosition().getX(), *it->getPosition().getY(), 50, 10);
	}

	for (std::vector<Rigidbody*>::iterator it = listOfRigidbody.begin(); it != listOfRigidbody.end(); ++it) {
		drawSquare((*it)->GetPosition().getX(), (*it)->GetPosition().getY(), 40);
	}

}

void Display::drawIntermediatePhysics(const float alpha)
{
	auto listOfParticles = m_linkedPhysics->getIntermediateParticle(alpha);
	auto listOfRigidbody = m_linkedPhysics->getIntermediateRigidbody(alpha);

	for (std::vector<Particle*>::iterator it = listOfParticles.begin(); it != listOfParticles.end(); ++it) {
		//drawCircle((it)->getPosition().getX(), (*it)->getPosition().getY(), 50, 10);
	}


	for (std::vector<Rigidbody*>::iterator it = listOfRigidbody.begin(); it != listOfRigidbody.end(); ++it) {
		drawSquare((*it)->GetPosition().getX(), (*it)->GetPosition().getY(), 40);
	}

	for (int i = 0; i < listOfParticles.size(); i++) {
		delete listOfParticles[i];
	}

	for (int i = 0; i < listOfRigidbody.size(); i++) {
		delete listOfRigidbody[i];
	}
}

void Display::drawCircle(float cx, float cy, float r, int num_segments)		//Fonction récupérée sur stackOverflow à cette adresse: https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f((x + cx) / (float)width, (y + cy) / (float)height);//output vertex 
	}
	glEnd();
}

void Display::drawSquare(float cx, float cy, float d)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glBegin(GL_LINE_LOOP);
	glVertex2f((-d + cx) / (float)width, (-d + cy) / (float)height);//output vertex 
	glVertex2f((d + cx) / (float)width, (-d + cy) / (float)height);//output vertex 
	glVertex2f((d + cx) / (float)width, (d + cy) / (float)height);//output vertex 
	glVertex2f((-d + cx) / (float)width, (d + cy) / (float)height);//output vertex 
	glEnd();
}

#pragma endregion

#pragma region Methods Libraries

void Display::initDisplayLib(int windowSizeX, int windowSizeY)
{
	//GLFW initialization
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(windowSizeX, windowSizeY, "OpenGL Example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}

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

	projectileMap = { 
		"Boulet de Canon",
		"Boule de feu",
		"Laser",
		"Balle"
	};
	selected = -1;
}

GLFWwindow* Display::getWindow()
{
	return window;
}

const bool Display::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Display::setupView()
{
	//Setup View
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);

}


void Display::shootProjectile(int projectileId)
{
	if (projectileId != -1)
	{
		Particle* particle = nullptr;
		std::vector<ParticleForceGenerator*> generators;
		ParticleGravity gravity;

		switch (projectileId) {
		case 0:
			std::cout << "vous avez choisi le boulet de canon" << std::endl;
			particle = new Particle(0.01f, 1, Vector3D(0, 0, 0), Vector3D(0, 20, 0), Vector3D(0, 0, 0));
			generators.push_back(new ParticleGravity());
			break;

		case 1:
			std::cout << "vous avez choisi la boule de feu" << std::endl;
			particle = new Particle(0.05f, 1, Vector3D(0, 0, 0), Vector3D(1, 2, 1), Vector3D(0, 0, 0));
			generators.push_back(new ParticleGravity(Vector3D(0,-5,0)));
			break;

		case 2:
			std::cout << "vous avez choisi le laser" << std::endl;
			particle = new Particle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0));
			generators.push_back(new ParticleGravity(Vector3D(0, 0, 0)));
			break;

		case 3:
			std::cout << "vous avez choisi la balle" << std::endl;
			particle = new Particle(0.99f, 1, Vector3D(0, 0, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0));
			generators.push_back(new ParticleGravity());
			break;

		default:
			break;
		}

		m_linkedPhysics->addParticle(particle, generators);
	}
}

void Display::swapBuffers()
{
	//Swap buffer and check for events
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Display::quitLibraries()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate;
}

void Display::terminalCommand()	//Non utilisé, mais gardé au cas ou
{
	std::cout << "Bienvenue au stand de tir\nVeuillez choisir votre projectile.\n1 : Boulet de canon\n2 : Boule de feu\n3 : Laser\n4 : Balle\n5 : Projectile modifiable\nLes vecteurs sont au format(x,y,z)" << std::endl;
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1: std::cout << "vous avez choisi le boulet de canon" << std::endl;
		m_linkedPhysics->addParticle(0.01, 1, Vector3D(0, 0, 0), Vector3D(1, -5, 3), Vector3D(0, 0, 0));
		break;
	case 2: std::cout << "vous avez choisi la boule de feu" << std::endl;
		m_linkedPhysics->addParticle(0.05, 1, Vector3D(0, 0, 0), Vector3D(1, 2, 1), Vector3D(0, 0, 0));
		break;
	case 3: std::cout << "vous avez choisi le laser" << std::endl;
		m_linkedPhysics->addParticle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0));
		break;
	case 4: std::cout << "vous avez choisi la balle" << std::endl;
		m_linkedPhysics->addParticle(0.99, 1, Vector3D(0, 0, 0), Vector3D(10, 10, 0), Vector3D(0, 0, 0));
		break;
	case 5: std::cout << "vous avez choisi le projectile personnel" << std::endl;
		break;
	default:
		return;

	}
}

Camera* Display::getCamera()
{
	return m_camera;
}

void Display::tick(std::vector<Entity*> entities)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		ShapeRenderer* shapeRenderer = entities[i]->getComponent<ShapeRenderer>();
		if (shapeRenderer != nullptr)
		{
			shapeRenderer->render(this);
		}
	}
}

void Display::createCubeVAO()
{
	float vertices[] = {

		//back face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		//front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		//left face
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		//right face
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		 //bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		//top face
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	unsigned int VBO;
	glGenVertexArrays(1, &m_cubeVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind everything
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int Display::getCubeVAO()
{
	return m_cubeVAO;
}


void Display::renderUI(std::vector<Entity*> entities)
{
	//RENDER UI

	//Create new ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		/*if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}*/
		if (ImGui::BeginMenu("Show"))
		{
			if (ImGui::MenuItem("Scene", NULL, &sceneWindowOpened)) {}
			if (ImGui::MenuItem("Demo", NULL, &demoWindowOpened)) {}
			if (ImGui::MenuItem("Debug", NULL, &debugWindowOpened)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Controls", NULL, &helpWindowOpened)) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// Stand de tir
	/*if (ImGui::Begin("Stand de tir"))
	{
		ImGui::Text("Bienvenue au stand de tir\n");
		ImGui::Text("Veuillez choisir votre projectile.\n");
		if (ImGui::TreeNode("Liste des projectiles")) {
			for (std::vector<std::string>::iterator it = projectileMap.begin(); it != projectileMap.end(); ++it) {
				if (ImGui::Selectable(it->c_str(), selected == std::distance(projectileMap.begin(), it))) {
					selected = std::distance(projectileMap.begin(), it);
					sprintf_s(projectileName, "%s", it->c_str());
				}
			}
			ImGui::TreePop();
		}
		if (ImGui::Button("Shoot"))
		{
			shootProjectile(selected);
		}
		ImGui::End();
	}*/

	//Scene window
	if (sceneWindowOpened)
		showSceneWindow(&sceneWindowOpened, entities);
	//Demo window
	if (demoWindowOpened)
		showDemoWindow(&demoWindowOpened);
	//Debug window
	if (debugWindowOpened)
		showDebugWindow(&debugWindowOpened);
	//Help window
	if (helpWindowOpened)
		showHelpWindow(&helpWindowOpened);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Display::showDemoWindow(bool* p_open)
{
	if (ImGui::Begin("Demo", p_open, ImGuiWindowFlags_NoCollapse))
	{
		//Combo of the available demos
		//button to start the demo
		ImGui::End();
	}
}
void Display::showSceneWindow(bool* p_open, std::vector<Entity*> entities)
{
	if (ImGui::Begin("Scene", p_open, ImGuiWindowFlags_NoCollapse))
	{
		for (size_t i = 0; i < entities.size(); i++) {
			if (ImGui::CollapsingHeader(entities[i]->getName().c_str())) {
				for (size_t j = 0; j < entities[i]->getComponents().size(); j++) {
					std::string treeNodeName;
					treeNodeName.append(entities[i]->getComponents()[j]->getName());
					treeNodeName.append("##");
					treeNodeName.append(std::to_string(entities[i]->id));
					if (ImGui::TreeNode(treeNodeName.c_str())) {
						entities[i]->getComponents()[j]->renderComponentUI();
						ImGui::TreePop();
					}
				}
			}
		}
		ImGui::End();
	}
}
void Display::showDebugWindow(bool* p_open)
{
	if (ImGui::Begin("Debug", p_open, ImGuiWindowFlags_NoCollapse))
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
		ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
		ImGui::Text("%d active allocations", io.MetricsActiveAllocations);
		ImGui::End();
	}
}

void Display::showHelpWindow(bool* p_open)
{
	if (ImGui::Begin("Help", p_open, ImGuiWindowFlags_NoCollapse))
	{
		ImGui::Text("Controls");
		ImGui::Spacing();
		ImGui::Text("Drag an input field to modify its value");
		ImGui::Text("Control + click on an input field to write a custom value");
		ImGui::Text("Hold right click + WASD to move the camera into the scene");
		ImGui::End();
	}
}
#pragma endregion