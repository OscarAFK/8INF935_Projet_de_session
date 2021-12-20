#include "BoxCollider.h"

void BoxCollider::Initialize(Vector3D halfSize, Matrix34 * offset)
{
    m_halfSize = halfSize;
    m_offset = offset;
}

const Vector3D& BoxCollider::getVertex(int i) const
{
	return m_vertices[i];
}

/*Vector3D* BoxCollider::getVertices() const
{
	return &m_vertices;
}*/

Vector3D BoxCollider::getHalfSize() const
{
	return m_halfSize;
}

void BoxCollider::setHalfSize(Vector3D halfSize)
{
	m_halfSize = halfSize;
}


colliderShapes BoxCollider::getShape() const
{
    return colliderShapes::BOX;
}

void BoxCollider::renderComponentUI()
{
	std::string hideLabelString = "##";

	/*
	std::string offsetStr;
	offsetStr.append(hideLabelString);
	offsetStr.append(std::to_string(m_owner->id));
	offsetStr.append("Offset");
	*/

	std::string halfSizeStr;
	halfSizeStr.append(hideLabelString);
	halfSizeStr.append(std::to_string(m_owner->id));
	halfSizeStr.append("Halfsize");
	/*
	float pos[3];
	std::vector<float> pos2 = m_offset->getPosition().getValues();

	std::copy(pos2.begin(), pos2.end(), pos);

	ImGui::Text("Offset: "); ImGui::SameLine(); ImGui::DragFloat3(offsetStr.c_str(), pos, 0.1f);
	m_offset.setPosition(Vector3D(pos));

	float rot[3];
	std::vector<float> rot2 = m_offset.getRotation().ToEuler().getValues();

	std::copy(rot2.begin(), rot2.end(), rot);

	ImGui::Text("Offset: "); ImGui::SameLine(); ImGui::DragFloat3(offsetStr.c_str(), rot, 0.1f);
	m_offset.setRotation(Quaternion(Vector3D(rot)));
	*/

	float halfSize[3];
	std::vector<float> halfSize2 = m_halfSize.getValues();

	std::copy(halfSize2.begin(), halfSize2.end(), halfSize);

	ImGui::Text("Half Size"); ImGui::SameLine(); ImGui::DragFloat3(halfSizeStr.c_str(), halfSize, 0.1f);
	setHalfSize(Vector3D(halfSize));
}
