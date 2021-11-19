#include "Display.h"
#include <map>


#define WINDOW_SIZE_X	480
#define WINDOW_SIZE_Y	480


#pragma region FunctionShaders
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

#pragma endregion

#pragma region Constructors

Display::Display(Physics* physics) : m_linkedPhysics(physics)
{	
	initDisplayLib();
}

#pragma endregion

#pragma region Mutex

void Display::linkToPhysics(Physics *physics)
{
	m_linkedPhysics = physics;
}

#pragma endregion

#pragma region Methods Class

void Display::drawPhysics()
{
	auto listOfParticles = m_linkedPhysics->getAllParticle();
	
	for (std::vector<Particle>::iterator it = listOfParticles->begin(); it != listOfParticles->end(); ++it) {
		drawCircle(it->getPosition().getX(), it->getPosition().getY(), 50, 10);
	}
}

void Display::drawIntermediatePhysics(const float alpha)
{
	auto listOfParticles = m_linkedPhysics->getIntermediateParticle(alpha);

	for (std::vector<Particle*>::iterator it = listOfParticles.begin(); it != listOfParticles.end(); ++it) {
		drawCircle((*it)->getPosition().getX(), (*it)->getPosition().getY(), 50, 10);
	}

	for (int i = 0; i < listOfParticles.size(); i++) {
		delete listOfParticles[i];
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

void Display::initDisplayLib()
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
	window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "OpenGL Example", NULL, NULL);
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

	float positions[6] = {
		-0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};


	//Vertex buffer
	/*unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);*/

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

	shader = CreateShader(vertexShader, FragmentShader);
	glUseProgram(shader);


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

void Display::setupView() // Add update camera here ------------------------------------------------------------------------------------------------
{
	//Setup View
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT);

	//camera->updateView();
}

void Display::renderUI()
{
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

	ImGui::Begin("Blob");
	if (ImGui::Button("Creer un blob"))
	{
		Particle* particle1 = new Particle(0.01f, 1, Vector3D(50, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
		Particle* particle2 = new Particle(0.01f, 1, Vector3D(-50, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
		Particle* particle3 = new Particle(0.01f, 1, Vector3D(-50, 50, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
		Particle* particle4 = new Particle(0.01f, 1, Vector3D(50, 50, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));
		Particle* particle5 = new Particle(0.01f, 1, Vector3D(0, 75, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0));

		m_linkedPhysics->addParticleContactGenerator(new ParticleCable(particle1, particle2, 300, 0.5f));
		m_linkedPhysics->addParticleContactGenerator(new ParticleCable(particle2, particle3, 300, 0.5f));
		m_linkedPhysics->addParticleContactGenerator(new ParticleCable(particle3, particle4, 300, 0.5f));
		m_linkedPhysics->addParticleContactGenerator(new ParticleCable(particle4, particle5, 300, 0.5f));
		m_linkedPhysics->addParticleContactGenerator(new ParticleCable(particle5, particle1, 300, 0.5f));

		std::vector<ParticleForceGenerator*> forceGenerators1;
		std::vector<ParticleForceGenerator*> forceGenerators2;
		std::vector<ParticleForceGenerator*> forceGenerators3;
		std::vector<ParticleForceGenerator*> forceGenerators4;
		std::vector<ParticleForceGenerator*> forceGenerators5;

		forceGenerators1.push_back(new ParticleSpring(particle5, 10, 50));
		forceGenerators2.push_back(new ParticleSpring(particle1, 10, 50));
		forceGenerators3.push_back(new ParticleSpring(particle2, 10, 50));
		forceGenerators4.push_back(new ParticleSpring(particle3, 10, 50));
		forceGenerators5.push_back(new ParticleSpring(particle4, 10, 50));

		m_linkedPhysics->addParticle(particle1, forceGenerators1);
		m_linkedPhysics->addParticle(particle2, forceGenerators2);
		m_linkedPhysics->addParticle(particle3, forceGenerators3);
		m_linkedPhysics->addParticle(particle4, forceGenerators4);
		m_linkedPhysics->addParticle(particle5, forceGenerators5);
		
	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
	glDeleteProgram(shader);
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
	return camera;
}

#pragma endregion