#include "PlaneCollider.h"

void PlaneCollider::Initialize(Vector3D normal, Vector3D offset)
{
    m_normal = normal;
    setOffset(offset);
}

Vector3D PlaneCollider::getNormal()
{
	return m_normal;
}

void PlaneCollider::setNormal(Vector3D normal)
{
	m_normal = normal;
}

colliderShapes PlaneCollider::getShape()
{
    return colliderShapes::PLANE;
}

void PlaneCollider::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string offsetStr;
	offsetStr.append(hideLabelString);
	offsetStr.append(std::to_string(m_owner->id));
	offsetStr.append("Offset");

	std::string normalStr;
	normalStr.append(hideLabelString);
	normalStr.append(std::to_string(m_owner->id));
	normalStr.append("Normal");

	float off[3];
	std::vector<float> off2 = getOffset().getValues();

	std::copy(off2.begin(), off2.end(), off);

	ImGui::Text("Offset: "); ImGui::SameLine(); ImGui::DragFloat3(offsetStr.c_str(), off, 0.1f);
	setOffset(Vector3D(off));

	float normal[3];
	std::vector<float> normal2 = getOffset().getValues();

	std::copy(normal2.begin(), normal2.end(), normal);

	ImGui::Text("Half Size"); ImGui::SameLine(); ImGui::DragFloat3(normalStr.c_str(), normal, 0.1f);
	setNormal(Vector3D(normal));
}
