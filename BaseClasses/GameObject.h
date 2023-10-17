#pragma once
#ifndef BASECLASS_GAMEOBJECT_H
#define BASECLASS_GAMEOBJECT_H

#include <string>

#include "SFML/Graphics.hpp"

#include "Enums/ComponentType.h"

#include "Component.h"
#include "Vector3D.h"

#include "../Entities/Components/Input/GeneralInput.h"
#include "../Entities/Components/Renderer/Renderer.h"

namespace baseclass
{
	using namespace component;

	class GameObject
	{
	public:
		GameObject(std::string name);
		virtual ~GameObject() = default;

		virtual void Initialize() = 0;
        virtual void ProcessInput(sf::Event event);
        virtual void Update(sf::Time deltaTime);
		virtual void PhysicsUpdate(sf::Time deltaTime);
        virtual void Draw(sf::RenderWindow* window, sf::RenderStates renderStates);

		virtual Vector3D GetPosition();
		virtual void SetPosition(Vector3D position);
		virtual void Move(Vector3D displacement);

		void AttachComponent(Component* component);
        void DetachComponent(Component* component);
        Component* FindComponentByName(std::string name);
        std::vector<Component*> GetComponents(ComponentType componentType);

		std::string GetName();
		sf::Sprite* GetSprite();

		bool GetEnabledStatus();
		virtual void SetEnabledStatus(bool status);
		

	protected:
		bool isEnabled;
		std::string name;
		sf::Sprite* sprite;

		std::vector<Component*> componentList;
	};
}

#endif // !GAMECORE_GAMEOBJECT_H
