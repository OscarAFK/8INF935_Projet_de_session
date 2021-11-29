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
	Transform(Entity* owner) : Component(owner)
	{
		m_name = "Transform";
	}
	/*
	void setPosition(Vector3D position);
	Vector3D getPosition();

	void setRotation(Vector3D rotation);
	Vector3D getRotation();

	void setScale(Vector3D scale);
	Vector3D getScale();
	*/
	void renderComponentUI()
	{
		ImGui::DragFloat3("Position", m_position, 0.005f);
		ImGui::DragFloat3("Rotation", m_rotation, 0.005f);
		ImGui::DragFloat3("Scale", m_scale, 0.005f);
	}
};
