#pragma once
#include <vector>;
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape
{
protected:
	glm::vec3 m_position, m_size;
	unsigned int m_VBO, m_VAO;
	Shader* m_shader;
public:
	Shape(glm::vec3 position, glm::vec3 size, Shader* shader)
	{
		m_position = position;
		m_size = size;
		m_shader = shader;
	}
	virtual void render(Display* display) = 0;

	glm::vec3 getPosition() 
	{
		return m_position;
	}
};