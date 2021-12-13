#include "PlaneCollider.h"

void PlaneCollider::Initialize(Vector3D normal, Vector3D offset)
{
    m_normal = normal;
    setOffset(offset);
}

Vector3D PlaneCollider::getNormal() const
{
	return m_normal;
}

float PlaneCollider::getPlaneOffset() const
{
	return m_planeOffset;
}

void PlaneCollider::setNormal(Vector3D normal)
{
	m_normal = normal;
}

colliderShapes PlaneCollider::getShape() const
{
    return colliderShapes::PLANE;
}

void PlaneCollider::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string offsetStr;
	offsetStr.append(hideLabelString);
	offsetStr.append(std::to_string(m_owner->id));
	offsetStr.append("PlaneOffset");

	std::string normalStr;
	normalStr.append(hideLabelString);
	normalStr.append(std::to_string(m_owner->id));
	normalStr.append("Normal");

	float off = getPlaneOffset();
	
	ImGui::Text("Plane Offset: "); ImGui::SameLine(); ImGui::DragFloat(offsetStr.c_str(), &off, 0.1f);
	m_planeOffset = off;

	float normal[3];
	std::vector<float> normal2 = getNormal().getValues();

	std::copy(normal2.begin(), normal2.end(), normal);

	ImGui::Text("Half Size"); ImGui::SameLine(); ImGui::DragFloat3(normalStr.c_str(), normal, 0.1f);
	setNormal(Vector3D(normal));
}
