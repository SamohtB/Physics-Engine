#pragma once
#ifndef COMPONENT_OBJECT_LIFE_TIME_H
#define COMPONENT_OBJECT_LIFE_TIME_H

#include "../../../BaseClasses/Component.h"
#include "../../../BaseClasses/GameObject.h"

namespace component
{
	using namespace baseclass;

	class ObjectLifeTime : public Component 
	{
	public:
		ObjectLifeTime(std::string name, float lifeTime);
		void Perform();

	private:
		float lifeTime;
		float ticks;
	};
}

#endif // !COMPONENT_OBJECT_LIFE_TIME_H



