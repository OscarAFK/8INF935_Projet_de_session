#include "Rigidbody.h"
/*
Rigidbody::Rigidbody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix33 tenseurInertie) :
	m_position(position), m_orientation(orientation), m_inverseMass(1 / mass), m_damping(damping), m_angularDamping(angularDamping),
	m_forceAccum(Vector3D(0, 0, 0)), m_torqueAccum(Vector3D(0, 0, 0))
{
	CalculateDerivedData();
	SetInertiaTenseur(tenseurInertie);
}

Rigidbody::Rigidbody(Vector3D position)
{
	m_position = position;
}*/

Rigidbody::Rigidbody(Entity* owner) : Component(owner)
{
	m_name = "Rigidbody";
	m_inverseMass = 1.0f;
	m_forceAccum = Vector3D(0, 0, 0);
	m_torqueAccum = Vector3D(0, 0, 0);
	float* position = m_owner->transform->getPosition();
	float* rotation = m_owner->transform->getRotation();
	m_position = Vector3D(position);
	m_orientation = Quaternion(1, 0, 0, 0);
	m_orientation.RotateByVector(rotation);
	m_isSleeping = true;
}

void Rigidbody::Initialize(float mass, float damping, float angularDamping, Matrix33 tenseurInertie)
{
	m_inverseMass = 1 / mass;
	m_damping = damping;
	m_angularDamping = angularDamping;
	SetInertiaTenseur(tenseurInertie);
	CalculateDerivedData();
}

void Rigidbody::Integrate(float duration)
{
	if (!m_isSleeping)
	{
		//Acceleration
		Vector3D linearAcceleration = m_inverseMass * m_forceAccum;
		Vector3D angularAcceleration = m_inverseTenseurInertieWorld * m_torqueAccum;

		//Vitesse
		m_velocity = m_velocity * pow(m_damping, duration) + linearAcceleration * duration;
		m_rotation = m_rotation * pow(m_angularDamping, duration) + angularAcceleration * duration;

		//Position
		m_previousPos = m_position;
		m_position = m_position + m_velocity * duration;
		m_orientation.UpdateByAngularVelocity(m_rotation, duration);

		m_owner->transform->setPosition(m_position);
		m_owner->transform->setRotation(m_orientation.ToEuler() * 360 / (2 * M_PI));

		//Update datas
		CalculateDerivedData();
		ClearAccumulator();
		if (m_velocity.norm() < 0.05f && m_rotation.norm() < 0.05f)
		{
			m_isSleeping = true;
		}
	}
}

void Rigidbody::AddForce(const Vector3D& force)
{
	m_isSleeping = false;
	m_forceAccum += force;
}

void Rigidbody::AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint)
{
	AddForce(force);
	m_torqueAccum += Vector3D::vectProduct((m_position - worldPoint),force);
}

void Rigidbody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& localPoint)
{
	Vector3D world = LocalToWorld(localPoint);
	AddForceAtPoint(force, world);
}

void Rigidbody::ClearAccumulator()
{
	m_forceAccum = Vector3D(0, 0, 0);
	m_torqueAccum = Vector3D(0, 0, 0);
}

void Rigidbody::SetInertiaTenseur(const Matrix33& tenseurInertie)
{
	m_inverseTenseurInertie = tenseurInertie.Inverse();
}

float Rigidbody::GetMass() const
{
	if (m_inverseMass != 0) return 1 / m_inverseMass;
	std::cout << "ERROR: infinite mass" << std::endl;
	return -1;
}

Vector3D Rigidbody::GetPosition() const
{
	return m_position;
}

void Rigidbody::SetPosition(Vector3D newPos)
{
	m_position = newPos;
}


Vector3D Rigidbody::GetPreviousPosition() const
{
	return m_previousPos;
}

void Rigidbody::SetOrientation(Vector3D newPos)
{
	m_orientation.SetByEulerRotation(newPos);
}

Vector3D Rigidbody::GetVelocity()
{
	return m_velocity;
}

void Rigidbody::CalculateDerivedData()
{
	m_transformMatrix.SetRotationAndPosition(m_orientation, m_position);
	ComputeTenseurInertiaWorld(m_inverseTenseurInertieWorld);
}

void Rigidbody::ComputeTenseurInertiaWorld(Matrix33& inertiaTenseurWorld)
{
	Matrix33 transformMatrix33 = m_transformMatrix.ToMatrix33();
	inertiaTenseurWorld = transformMatrix33 * m_inverseTenseurInertie;
	inertiaTenseurWorld *= transformMatrix33.Inverse();
}

Vector3D Rigidbody::LocalToWorld(const Vector3D& local)
{
	return m_transformMatrix * local + m_position;
}

Vector3D Rigidbody::WorldToLocal(const Vector3D& world)
{
	return m_transformMatrix.Inverse() * (world - m_position);
}

Matrix33 tenseursFormesDeBase::Sphere(float m, float r) {
	float values[] = { 2 / 5.0f * m * r * r, 0,0,
						0,2 / 5.0f * m * r * r, 0,
						0,0,2 / 5.0f * m * r * r };
	return Matrix33(values);
}

Matrix33 tenseursFormesDeBase::Cuboide(float m, Vector3D d) {
	float values[] = { 1 / 12.0f * m * (d.getY() * d.getY() + d.getZ() * d.getZ()), 0,0,
						0,1 / 12.0f * m * (d.getX() * d.getX() + d.getZ() * d.getZ()), 0,
						0,0,1 / 12.0f * m * (d.getY() * d.getY() + d.getX() * d.getX()) };
	return Matrix33(values);
}

Matrix33 tenseursFormesDeBase::Cylindre(float m, float r, float h) {
	float values[] = { 1 / 12.0f * m * h * h + 1 / 4.0f * m * r * r, 0,0,
						0,1 / 2.0f * m * r * r, 0,
						0,0,1 / 12.0f * m * h * h + 1 / 4.0f * m * r * r };
	return Matrix33(values);
}


void Rigidbody::renderComponentUI(){

	std::string    hideLabelString = "##";

	std::string massStr;
	massStr.append(hideLabelString);
	massStr.append(std::to_string(m_owner->id));
	massStr.append("Mass");

	std::string dampStr;
	dampStr.append(hideLabelString);
	dampStr.append(std::to_string(m_owner->id));
	dampStr.append("Damping");

	std::string angDampStr;
	angDampStr.append(hideLabelString);
	angDampStr.append(std::to_string(m_owner->id));
	angDampStr.append("AngularDamping");

	std::string forceStr;
	forceStr.append(hideLabelString);
	forceStr.append(std::to_string(m_owner->id));
	forceStr.append("Force");

	float mass = GetMass();
	ImGui::Text("           Mass"); ImGui::SameLine(); ImGui::DragFloat(massStr.c_str(), &mass, 0.005f, 0.005f, 999999.9f);
	if (mass != GetMass()) {
		m_inverseMass = 1 / mass;
		SetInertiaTenseur(tenseursFormesDeBase::Cuboide(mass, Vector3D(1, 1, 1)));
	}
	ImGui::Text("        Damping"); ImGui::SameLine(); ImGui::DragFloat(dampStr.c_str(), &m_damping, 0.005f);
	ImGui::Text("Angular damping"); ImGui::SameLine(); ImGui::DragFloat(angDampStr.c_str(), &m_angularDamping, 0.005f);
	ImGui::Text("Speed (unite/s): \tX: %.2f\tY:%.2f\tZ:%.2f", m_velocity.getX(), m_velocity.getY(), m_velocity.getZ());
	ImGui::Text("Angular speed (rps): \tX: %.2f\tY:%.2f\tZ:%.2f", m_rotation.getX(), m_rotation.getY(), m_rotation.getZ());
	ImGui::Separator();
	ImGui::Text("FORCES: ");
	static float forceToAdd[3] = { 0.0f, 0.0f, 0.0f};
	ImGui::Text("Force to add: "); ImGui::SameLine(); ImGui::DragFloat3(forceStr.c_str(), forceToAdd, 0.1f);
	
	if (ImGui::Button("Add force at center of gravity")) {
		AddForce(Vector3D(forceToAdd));
	}
	ImGui::SameLine();
	if (ImGui::Button("Add force at random point")) {
		AddForceAtBodyPoint(Vector3D(forceToAdd), Vector3D(getRandomValue(0,1), getRandomValue(0, 1), getRandomValue(0, 1)));
	}
}

Matrix34 Rigidbody::GetTransformMatrix() const
{
	return m_transformMatrix;
}

float getRandomValue(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}
