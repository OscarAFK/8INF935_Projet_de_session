#include "SphereCollider.h"

void SphereCollider::Initialize(float radius, Vector3D offset)
{
    m_radius = radius;
}

float SphereCollider::getRadius() const
{
    return m_radius;
}

void SphereCollider::setRadius(float radius)
{
    m_radius = radius;
}

colliderShapes SphereCollider::getShape() const
{
    return colliderShapes::SPHERE;
}

void SphereCollider::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string radiusStr;
	radiusStr.append(hideLabelString);
	radiusStr.append(std::to_string(m_owner->id));
	radiusStr.append("Radius");

	ImGui::Text("Radius"); ImGui::SameLine(); ImGui::DragFloat(radiusStr.c_str(), &m_radius, 0.1f);
}
