#pragma once
#include <vector>;
#include "Shader.h"
#include "Display.h"

#include <GLFW/glfw3.h>

class Shape
{
protected:
	glm::vec3 m_position, m_rotation, m_scale;
	unsigned int m_VBO, m_VAO;
public:

	Shape(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
	}

	unsigned int getVAO()
	{
		return m_VAO;
	}

	glm::vec3 getPosition()
	{
		return m_position;
	}

	glm::vec3 getRotation()
	{
		return m_rotation;
	}

	glm::vec3 getScale()
	{
		return m_scale;
	}
};