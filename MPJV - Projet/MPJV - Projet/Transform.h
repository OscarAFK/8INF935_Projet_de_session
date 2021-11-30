#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "Vector3D.h"
#include "Utilitaire/Quaternion.h"

class Transform : public Component
{
private:
	float m_position[3] = { 0.0f, 0.0f, 0.0f};
	float m_rotation[3] = { 0.0f, 0.0f, 0.0f };
	float m_scale[3] = { 1.0f, 1.0f, 1.0f };

public:

	Transform(Entity* owner);
	
	void setPosition(Vector3D position);
	void addPosition(Vector3D position);
	float* getPosition();

	void setRotation(Vector3D rotation);
	void addRotation(Vector3D rotation);
	float* getRotation();

	//void setScale(Vector3D scale);
	float* getScale();
	
	void renderComponentUI();
};
