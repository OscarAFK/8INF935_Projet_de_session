#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class BoxCollider : public Collider
{
private:
	Vector3D m_halfSize;

    //std::vector<Vector3D> 
	Vector3D m_vertices[8] =
	{
		Vector3D(-m_halfSize.getX(), - m_halfSize.getY(), - m_halfSize.getZ()),
		Vector3D(-m_halfSize.getX(), - m_halfSize.getY(), + m_halfSize.getZ()),
		Vector3D(-m_halfSize.getX(), + m_halfSize.getY(), - m_halfSize.getZ()),
		Vector3D(-m_halfSize.getX(), + m_halfSize.getY(), + m_halfSize.getZ()),
		Vector3D(+m_halfSize.getX(), - m_halfSize.getY(), - m_halfSize.getZ()),
		Vector3D(+m_halfSize.getX(), - m_halfSize.getY(), + m_halfSize.getZ()),
		Vector3D(+m_halfSize.getX(), + m_halfSize.getY(), - m_halfSize.getZ()),
		Vector3D(+m_halfSize.getX(), + m_halfSize.getY(), + m_halfSize.getZ())
	};

public:

	BoxCollider(Entity* owner) : Collider(owner) { m_name = "Box Collider"; };
	void Initialize(Vector3D halfSize = Vector3D(0.5f, 0.5f, 0.5f), Matrix34 offset = Matrix34());

	const Vector3D& getVertex(int i) const;
	Vector3D* getVertices() const;
	Vector3D getHalfSize() const;
	void setHalfSize(Vector3D halfSize);

	colliderShapes getShape() const;

	void renderComponentUI();
};