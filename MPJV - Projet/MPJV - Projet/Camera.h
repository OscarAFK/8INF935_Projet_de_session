#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
class Camera {
private:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_cameraDirection;
	glm::mat4 m_view;
	float m_cameraSpeed = 0.05f;

public:
	Camera() {
		m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
		m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	}

	void updateView()
	{
		m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	}

	void moveCamera(glm::vec3 moveVector)
	{
		m_cameraPos += moveVector;
	}

	glm::vec3 getCameraUp()
	{
		return m_cameraUp;
	}

	glm::vec3 getCameraFront()
	{
		return m_cameraFront;
	}

};