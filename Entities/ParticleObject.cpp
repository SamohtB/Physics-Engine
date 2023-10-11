#include "ParticleObject.h"

using namespace entity;

ParticleObject::ParticleObject(std::string name) : GameObject(name)
{
	this->isEnabled = true;
	this->particle = nullptr;
	this->renderedObject = nullptr;
}

void ParticleObject::Initialize()
{

}

Vector3D ParticleObject::GetPosition()
{
	return this->particle->GetPosition();
}

void ParticleObject::SetPosition(Vector3D position)
{
	sf::Vector2f position2D = sf::Vector2f(position.x, position.y);
	this->renderedObject->setPosition(position2D);
	this->particle->SetPosition(position);
}

void ParticleObject::Move(Vector3D displacement) 
{
	this->SetPosition(this->particle->GetPosition() + displacement);
}

void ParticleObject::PhysicsUpdate(sf::Time deltaTime)
{
	particle->Integrate(deltaTime.asSeconds());
	this->renderedObject->setPosition(sf::Vector2f(particle->GetPosition().x, particle->GetPosition().y));
}

