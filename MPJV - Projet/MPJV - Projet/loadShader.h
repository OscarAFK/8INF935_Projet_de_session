#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
class loadShader
{
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

};

