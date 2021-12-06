#include "GravityForceGenerator.h"
#include <iostream>

void GravityForceGenerator::Initialize(Vector3D gravity)
{
	m_gravity = gravity;
}

void GravityForceGenerator::UpdateForce(Rigidbody* rg, float deltaTime)
{
	rg->AddForce(rg->GetMass() * m_gravity);
}

void GravityForceGenerator::renderComponentUI()
{
	std::string    hideLabelString = "##";

	std::string gravityStr;
	gravityStr.append(hideLabelString);
	gravityStr.append(std::to_string(m_owner->id));
	gravityStr.append("Gravity");
	float grav[3];
	std::vector<float> grav2 = m_gravity.getValues();
	
	std::copy(grav2.begin(), grav2.end(), grav);

	ImGui::Text("Gravity: "); ImGui::SameLine(); ImGui::DragFloat3(gravityStr.c_str(), grav, 0.1f);
	m_gravity.setX(grav[0]);
	m_gravity.setY(grav[1]);
	m_gravity.setZ(grav[2]);
}
