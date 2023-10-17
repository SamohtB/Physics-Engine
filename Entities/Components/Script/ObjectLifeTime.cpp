#include "ObjectLifeTime.h"

using namespace component;

ObjectLifeTime::ObjectLifeTime(std::string name, float lifeTime) : Component(name, ComponentType::SCRIPT)
{
	this->lifeTime = lifeTime;
	this->ticks = 0.0f;
}

void ObjectLifeTime::Perform()
{
	this->ticks += this->deltaTime.asSeconds();

	if(ticks >= this->lifeTime)
	{
		this->ticks = 0.0f;
		this->GetOwner()->SetEnabledStatus(false);
	}
}