#pragma once
#include <vector>;
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape
{
protected:
	glm::vec3 m_position;
	unsigned int m_VBO, m_VAO;
	Shader* m_shader;
public:
	Shape(glm::vec3 position)
	{
		m_position = position;
	}
	virtual void render(Display* display) = 0;
};