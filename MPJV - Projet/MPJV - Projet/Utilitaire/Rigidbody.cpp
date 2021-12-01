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
}

void Rigidbody::Initialize(float mass, float damping, float angularDamping, Matrix33 tenseurInertie)
{
	m_inverseMass = 1 / mass;
	m_damping = damping;
	m_angularDamping = angularDamping;
	CalculateDerivedData();
	SetInertiaTenseur(tenseurInertie);
}

void Rigidbody::Integrate(float duration)
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
	m_owner->transform->setRotation(m_orientation.ToEuler()*360/(2*M_PI));

	//Update datas
	CalculateDerivedData();
	ClearAccumulator();
}

void Rigidbody::AddForce(const Vector3D& force)
{
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

Vector3D Rigidbody::GetPreviousPosition() const
{
	return m_previousPos;
}


void Rigidbody::CalculateDerivedData()
{
	m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
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
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
	float mass = GetMass();
	ImGui::DragFloat("Mass", &mass, 0.005f, 0.005f, 999999.9f);
	if (mass != GetMass()) {
		m_inverseMass = 1 / mass;
		SetInertiaTenseur(tenseursFormesDeBase::Cuboide(mass, Vector3D(1, 1, 1)));
	}
	ImGui::DragFloat("Damping", &m_damping, 0.005f);
	ImGui::DragFloat("Angular damping", &m_angularDamping, 0.005f);
	ImGui::Text("Speed (unite/s): \tX: %.2f\tY:%.2f\tZ:%.2f", m_velocity.getX(), m_velocity.getY(), m_velocity.getZ());
	ImGui::Text("Angular speed (rps): \tX: %.2f\tY:%.2f\tZ:%.2f", m_rotation.getX(), m_rotation.getY(), m_rotation.getZ());
	ImGui::Separator();
	ImGui::Text("FORCES: ");
	static float forceToAdd[3] = { 0.0f, 0.0f, 0.0f};
	ImGui::Text("Force to add: "); ImGui::SameLine(); ImGui::DragFloat3("##Force to add: ", forceToAdd, 0.1f);
	
	if (ImGui::Button("Add force at center of gravity")) {
		AddForce(Vector3D(forceToAdd));
	}
	ImGui::SameLine();
	if (ImGui::Button("Add force at random point")) {
		AddForceAtBodyPoint(Vector3D(forceToAdd), Vector3D(getRandomValue(0,1), getRandomValue(0, 1), getRandomValue(0, 1)));
	}

	ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.35f);
}

float getRandomValue(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}
