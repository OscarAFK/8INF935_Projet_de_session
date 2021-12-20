#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "Vector3D.h"
#include "Utilitaire/Matrix34.h"
#include "Utilitaire/Quaternion.h"

class Transform : public Component
{
private:
	/*float m_position[3] = {0.0f, 0.0f, 0.0f};
	float m_rotation[3] = { 0.0f, 0.0f, 0.0f };
	float m_scale[3] = { 1.0f, 1.0f, 1.0f };*/

	Vector3D m_position = Vector3D(0, 0, 0);
	Quaternion m_orientation = Quaternion(1,0, 0, 0);
	Vector3D m_displayRotation = Vector3D(0, 0, 0);
	//Vector3D m_rotation = Vector3D(0, 0, 0);
	Vector3D m_scale = Vector3D(1, 1, 1);
	Matrix34 m_transformMatrix;

public:

	Transform(Entity* owner);
	
	void setPosition(Vector3D position);
	void translate(Vector3D position);
	Vector3D getPosition() const;

	void setRotation(Vector3D eulerRotation);
	void rotate(Vector3D eulerRotation);
	void setRotation(Quaternion rotation);
	void rotate(Quaternion rotation);
	Quaternion getRotation() const;
	Vector3D getDisplayRotation() const;

	Matrix34 getTransformMatrix() const;
	Matrix34 *getRefToTransformMatrix();

	Vector3D localToWorld(const Vector3D& local);
	Vector3D worldToLocal(const Vector3D& world);

	void setScale(Vector3D scale);
	void scale(Vector3D scale);
	Vector3D getScale() const;
	
	void renderComponentUI();
};
