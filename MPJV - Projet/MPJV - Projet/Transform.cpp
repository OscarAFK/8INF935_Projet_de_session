#include "Transform.h"
#include "Entity.h"

Transform::Transform(Entity* owner) : Component(owner)
{
	m_name = "Transform";
}

void Transform::setPosition(Vector3D position)
{
	m_position[0] = position.getX();
	m_position[1] = position.getY();
	m_position[2] = position.getZ();
}

void Transform::addPosition(Vector3D position)
{
	m_position[0] += position.getX();
	m_position[1] += position.getY();
	m_position[2] += position.getZ();
}

float* Transform::getPosition(){
	return m_position;
}

void Transform::setRotation(Vector3D rotation)
{
	m_rotation[0] = rotation.getX();
	m_rotation[1] = rotation.getY();
	m_rotation[2] = rotation.getZ();
}

void Transform::addRotation(Vector3D rotation)
{
	m_rotation[0] += rotation.getX();
	m_rotation[1] += rotation.getY();
	m_rotation[2] += rotation.getZ();
}

float* Transform::getRotation(){
	return m_rotation;
}

//void Transform::setScale(Vector3D scale){
//	m_scale = scale;
//}

float* Transform::getScale(){
	return m_scale;
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

	ImGui::Text(positionLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(positionStr.c_str(), m_position, 0.01f);
	ImGui::Text(rotationLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(rotationStr.c_str(), m_rotation, 0.01f);
	ImGui::Text(scaleLabelString.c_str()); ImGui::SameLine(); ImGui::DragFloat3(scaleStr.c_str(), m_scale, 0.01f);
}
