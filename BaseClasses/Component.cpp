#include "Component.h"

using namespace baseclass;

Component::Component(std::string name, ComponentType componentType)
{
	this->name = name;
	this->componentType = componentType;
	this->owner = nullptr;
}

Component::~Component()
{
	this->owner = nullptr;
    this->componentType = ComponentType::NONE;
}

void Component::AttachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::DetachOwner()
{
	delete this;
}

GameObject* Component::GetOwner()
{
	return this->owner;
}

ComponentType Component::GetType()
{
	return this->componentType;
}

std::string Component::GetName()
{
	return this->name;
}

void Component::SetDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}