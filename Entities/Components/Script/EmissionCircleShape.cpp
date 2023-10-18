#include "EmissionCircleShape.h"

using namespace component;


EmissionCircleShape::EmissionCircleShape(std::string name, ParticleSystem* particleSystem) : Component(name, ComponentType::SCRIPT)
{
	this->particleSystem = particleSystem;
	this->angle = 0.0f;
}

EmissionCircleShape::~EmissionCircleShape()
{
	delete this->particleSystem;
}

void EmissionCircleShape::Perform()
{
	this->angle += this->deltaTime.asSeconds() * 2.0f;
	this->angle = fmod(this->angle, 365.0);

	if (this->angle < 0) 
	{
		this->angle += 365.0; 
	}

	Vector3D currentPos = this->GetOwner()->GetPosition();

	float newX = 1000 * std::cosf(this->angle);
	float newY = 1000 * std::sinf(this->angle);

	this->particleSystem->SetEmissionVector(Vector3D(newX, newY, 0));
}