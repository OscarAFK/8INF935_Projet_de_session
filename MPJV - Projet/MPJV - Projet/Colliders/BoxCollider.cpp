#include "BoxCollider.h"

void BoxCollider::Initialize(Vector3D halfSize, Vector3D offset)
{
    m_halfSize = halfSize;
    setOffset(offset);
}

Vector3D BoxCollider::getHalfSize()
{
	return m_halfSize;
}

void BoxCollider::setHalfSize(Vector3D halfSize)
{
	m_halfSize = halfSize;
}


colliderShapes BoxCollider::getShape()
{
    return colliderShapes::BOX;
}

void BoxCollider::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string offsetStr;
	offsetStr.append(hideLabelString);
	offsetStr.append(std::to_string(m_owner->id));
	offsetStr.append("Offset");

	std::string halfSizeStr;
	halfSizeStr.append(hideLabelString);
	halfSizeStr.append(std::to_string(m_owner->id));
	halfSizeStr.append("Halfsize");

	float off[3];
	std::vector<float> off2 = getOffset().getValues();

	std::copy(off2.begin(), off2.end(), off);

	ImGui::Text("Offset: "); ImGui::SameLine(); ImGui::DragFloat3(offsetStr.c_str(), off, 0.1f);
	setOffset(Vector3D(off));


	float halfSize[3];
	std::vector<float> halfSize2 = getOffset().getValues();

	std::copy(halfSize2.begin(), halfSize2.end(), halfSize);

	ImGui::Text("Half Size"); ImGui::SameLine(); ImGui::DragFloat3(halfSizeStr.c_str(), halfSize, 0.1f);
	setHalfSize(Vector3D(halfSize));
}
