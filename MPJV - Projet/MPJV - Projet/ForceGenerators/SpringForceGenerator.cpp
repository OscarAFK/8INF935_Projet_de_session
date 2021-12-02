#include "SpringForceGenerator.h"
#include <iostream>

void SpringForceGenerator::Initialize(Vector3D bodyAnchor, Rigidbody* rgbd, Vector3D otherBodyAnchor, float k, float restLength)
{
	m_bodyAnchor = bodyAnchor;
	m_otherRgbd = rgbd;
	m_otherBodyAnchor = otherBodyAnchor;
	m_k = k;
	m_restLength = restLength;
}

void SpringForceGenerator::UpdateForce(Rigidbody* rg, float deltaTime)
{
	if (m_otherRgbd != nullptr) {
		Vector3D d = (rg->GetPosition() + m_bodyAnchor - (m_otherRgbd->GetPosition() + m_otherBodyAnchor));
		rg->AddForceAtBodyPoint(d.normalize()* (-m_k * (d.norm() - m_restLength)), m_bodyAnchor);
	}
	else {
		Vector3D d = m_otherBodyAnchor - (rg->GetPosition() + m_bodyAnchor);
		rg->AddForceAtBodyPoint(d.normalize() * (-m_k * (d.norm() - m_restLength)), m_bodyAnchor);
	}
}

void SpringForceGenerator::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string bodyAnchorStr;
	bodyAnchorStr.append(hideLabelString);
	bodyAnchorStr.append(std::to_string(m_owner->id));
	bodyAnchorStr.append("Body Anchor");

	std::string otherBodyAnchorStr;
	otherBodyAnchorStr.append(hideLabelString);
	otherBodyAnchorStr.append(std::to_string(m_owner->id));
	otherBodyAnchorStr.append("Other Body Anchor");

	std::string kStr;
	kStr.append(hideLabelString);
	kStr.append(std::to_string(m_owner->id));
	kStr.append("k");

	std::string restLengthStr;
	restLengthStr.append(hideLabelString);
	restLengthStr.append(std::to_string(m_owner->id));
	restLengthStr.append("Rest Length");

	//BODY ANCHOR
	float bodyAnchor[3];
	std::vector<float> bodyAnchor2 = m_bodyAnchor.getValues();
	std::copy(bodyAnchor2.begin(), bodyAnchor2.end(), bodyAnchor);

	ImGui::Text("Body Anchor: "); ImGui::SameLine(); ImGui::DragFloat3(bodyAnchorStr.c_str(), bodyAnchor, 0.01f);
	m_bodyAnchor.setX(bodyAnchor[0]);
	m_bodyAnchor.setY(bodyAnchor[1]);
	m_bodyAnchor.setZ(bodyAnchor[2]);

	//Other Rigidbody
	if(m_otherRgbd != nullptr) ImGui::Text("Another rigidbody has been set.");
	else ImGui::Text("No rigidbody set.");

	//OTHER BODY ANCHOR
	float otherBodyAnchor[3];
	std::vector<float> otherBodyAnchor2 = m_bodyAnchor.getValues();
	std::copy(otherBodyAnchor2.begin(), otherBodyAnchor2.end(), otherBodyAnchor);

	ImGui::Text("Body Anchor: "); ImGui::SameLine(); ImGui::DragFloat3(otherBodyAnchorStr.c_str(), otherBodyAnchor, 0.01f);
	m_bodyAnchor.setX(otherBodyAnchor[0]);
	m_bodyAnchor.setY(otherBodyAnchor[1]);
	m_bodyAnchor.setZ(otherBodyAnchor[2]);

	//OTHERS
	ImGui::Text("k"); ImGui::SameLine(); ImGui::DragFloat(kStr.c_str(), &m_k, 0.005f);
	ImGui::Text("Rest length"); ImGui::SameLine(); ImGui::DragFloat(restLengthStr.c_str(), &m_restLength, 0.005f);
}
