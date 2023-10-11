#pragma once
#ifndef BASECLASS_COMPONENT_H
#define BASECLASS_COMPONENT_H

#include "SFML/Graphics.hpp"

#include <string>

#include "Enums/ComponentType.h"

namespace baseclass
{
	class GameObject;

	class Component
	{
	protected:
		GameObject* owner;
        ComponentType componentType;
        std::string name;
        sf::Time deltaTime;

	public:
		Component(std::string name, ComponentType componentType);
		virtual ~Component();

		void AttachOwner(GameObject* pOwner);
		void DetachOwner();

		virtual void Perform() = 0;

		GameObject* GetOwner();
		ComponentType GetType();
		std::string GetName();
		void SetDeltaTime(sf::Time deltaTime);
	};
}


#endif // !BASECLASS_COMPONENT_H



