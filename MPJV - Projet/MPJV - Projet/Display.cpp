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
		drawCircle(it->getPosition().getX(), it->getPosition().getY(), 10, 4);
	}
}

void Display::drawIntermediatePhysics(const float alpha)
{
	auto listOfParticles = m_linkedPhysics->getIntermediateParticle(alpha);

	for (std::vector<Particle>::iterator it = listOfParticles->begin(); it != listOfParticles->end(); ++it) {
		drawCircle(it->getPosition().getX(), it->getPosition().getY(), 10, 4);
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

#pragma endregion

#pragma region Methods Libraries

void Display::initDisplayLib()
{
	//GLFW initialization
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "OpenGL Example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
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
		//Le -10 dans l'accélération représente la gravité
	{ "Boulet de Canon", Particle(0.01f, 1, Vector3D(0, 0, 0), Vector3D(40, 10, 0), Vector3D(0, -10, 0)) },
	{ "Boule de feu", Particle(0.05, 1, Vector3D(0, 0, 0), Vector3D(20, 40, 0), Vector3D(0, -10, 0)) },
	{ "Laser", Particle(10000, 1, Vector3D(0, 0, 0), Vector3D(500, 0, 0), Vector3D(0, 0, 0))},
	{ "Balle", Particle(0.99, 1, Vector3D(0, 0, 0), Vector3D(80, 80, 0), Vector3D(0, -10, 0))}
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
			std::cout << projectileName << " shot" << std::endl;
			m_linkedPhysics->addParticle(projectileMap.find(projectileName)->second);
		}
	}
	ImGui::End();


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

#pragma endregion