#include "SphereCollider.h"

void SphereCollider::Initialize(float radius, Vector3D offset)
{
    m_radius = radius;
    setOffset(offset);
}

float SphereCollider::getRadius()
{
    return m_radius;
}

void SphereCollider::setRadius(float radius)
{
    m_radius = radius;
}

colliderShapes SphereCollider::getShape()
{
    return colliderShapes::SPHERE;
}

void SphereCollider::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string offsetStr;
	offsetStr.append(hideLabelString);
	offsetStr.append(std::to_string(m_owner->id));
	offsetStr.append("Offset");

	std::string radiusStr;
	radiusStr.append(hideLabelString);
	radiusStr.append(std::to_string(m_owner->id));
	radiusStr.append("Radius");

	float off[3];
	std::vector<float> off2 = getOffset().getValues();

	std::copy(off2.begin(), off2.end(), off);

	ImGui::Text("Offset: "); ImGui::SameLine(); ImGui::DragFloat3(offsetStr.c_str(), off, 0.1f);
	setOffset(Vector3D(off));

	ImGui::Text("Radius"); ImGui::SameLine(); ImGui::DragFloat(radiusStr.c_str(), &m_radius, 0.1f);
}
