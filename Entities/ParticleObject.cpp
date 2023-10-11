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
	this->particle = new Particle3D();
	this->renderedObject = new sf::CircleShape();
	this->renderedObject->setRadius(25.0f);
	this->renderedObject->setFillColor(sf::Color::White);
	this->renderedObject->setOutlineColor(sf::Color::Black);

	Renderer* renderer = new Renderer(this->name + " Renderer");
	renderer->AssignDrawable(this->renderedObject);

	this->componentList.push_back(renderer);
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

Particle3D* ParticleObject::GetParticle()
{
	return this->particle;
}

