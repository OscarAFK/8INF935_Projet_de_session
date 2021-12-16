#include "Transform.h"
#include "Entity.h"
#include "Utilitaire/Rigidbody.h"

Transform::Transform(Entity* owner) : Component(owner)
{
	m_name = "Transform";
}

void Transform::setPosition(Vector3D position)
{
	m_position = position;
}

void Transform::translate(Vector3D position)
{
	m_position += position;
}

Vector3D Transform::getPosition() const{
	return m_position;
}

void Transform::setRotation(Vector3D eulerRotation)
{
	m_orientation.SetByEulerRotation(eulerRotation * 2 * M_PI / 360.0f);
	m_displayRotation = m_orientation.ToEuler() * 360 / (2 * M_PI);
}

void Transform::rotate(Vector3D eulerRotation)
{
	m_orientation.SetByEulerRotation(m_orientation.ToEuler() + eulerRotation * 2 * M_PI / 360.0f);
	m_displayRotation = m_orientation.ToEuler() * 360 / (2 * M_PI);
}

void Transform::setRotation(Quaternion rotation)
{
	m_orientation = rotation;
	m_displayRotation = m_orientation.ToEuler() * 360 / (2 * M_PI);
}

void Transform::rotate(Quaternion rotation)
{
	m_orientation *= rotation;
	m_displayRotation = m_orientation.ToEuler() * 360 / (2 * M_PI);
}

Quaternion Transform::getRotation() const{
	return m_orientation;
}

Vector3D Transform::getDisplayRotation() const
{
	return m_displayRotation;
}

void Transform::setScale(Vector3D scale){
	m_scale = scale;
}

void Transform::scale(Vector3D scale) {
	m_scale = Vector3D(m_scale.getX() * scale.getX(),
					   m_scale.getY() * scale.getY(),
					   m_scale.getZ() * scale.getZ());
}

Vector3D Transform::getScale() const{
	return m_scale;
}

Matrix34 Transform::getTransformMatrix() const
{
	Matrix34 transform = Matrix34();
	transform.SetRotationAndPosition(m_orientation, m_position);
	return transform;
}

Vector3D Transform::localToWorld(const Vector3D& local)
{
	return getTransformMatrix() * local + m_position;
}

Vector3D Transform::worldToLocal(const Vector3D& world)
{
	return getTransformMatrix().Inverse() * (world - m_position);
}


void Transform::renderComponentUI()
{
	ImGui::PushItemWidth(0);

	std::string hideLabelString = "##";
	std::string positionLabelString = "Position";
	std::string rotationLabelString = "Rotation";
	std::string    scaleLabelString = "   Scale";

	std::string positionStr;
	positionStr.append(hideLabelString);
	positionStr.append(std::to_string(m_owner->id));
	positionStr.append(positionLabelString);

	std::string rotationStr;
	rotationStr.append(hideLabelString);
	rotationStr.append(std::to_string(m_owner->id));
	rotationStr.append(rotationLabelString);

	std::string scaleStr;
	scaleStr.append(hideLabelString);
	scaleStr.append(std::to_string(m_owner->id));
	scaleStr.append(scaleLabelString);

	float pos[3];
	std::vector<float> pos2 = m_position.getValues();
	std::copy(pos2.begin(), pos2.end(), pos);
	ImGui::Text(positionLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(positionStr.c_str(), pos, 0.01f);
	m_position = Vector3D(pos);
	/*if (m_owner->getComponent<Rigidbody>() != nullptr && (m_position[0] != oldPos[0] || m_position[1] != oldPos[1] || m_position[2] != oldPos[2])) {
		m_owner->getComponent<Rigidbody>()->SetPosition(Vector3D(m_position));
	}*/

	float rot[3];
	std::vector<float> rot2 = m_displayRotation.getValues();
	std::copy(rot2.begin(), rot2.end(), rot);
	ImGui::Text(rotationLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(rotationStr.c_str(), rot, 0.01f);
	setRotation(Vector3D(rot));
	//m_rotation = Vector3D(rot);

	/*if (m_owner->getComponent<Rigidbody>() != nullptr && (m_rotation[0] != oldRot[0] || m_rotation[1] != oldRot[1] || m_rotation[2] != oldRot[2])) {
		m_owner->getComponent<Rigidbody>()->SetOrientation(Vector3D(m_rotation) * (2 * M_PI) / 360);
	}*/

	float scale[3];
	std::vector<float> scale2 = m_scale.getValues();
	std::copy(scale2.begin(), scale2.end(), scale);
	ImGui::Text(scaleLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(scaleStr.c_str(), scale, 0.01f);
	m_scale = Vector3D(scale);

	//std::cout << m_position.to_string();//, m_rotation.ToEuler().to_string(), m_scale.to_string());
}
