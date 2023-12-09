#pragma once
#ifndef ENTITY_BOX_2D_H
#define ENTITY_BOX_2D_H

#include "SFML/Graphics.hpp"
#include "../BaseClasses/GameObject.h"
#include "../Physics/Rigidbodies/Rigidbody2D.h"
#include "../Physics/Rigidbodies/Shape2D.h"
#include "../Physics/Rigidbodies/NarrowPhase.h"

namespace entity
{
	using namespace baseclass;
	using namespace physics;

	class Box2D : public GameObject
	{
	public:
		Rigidbody2D body;
		RectShape2D shape;
		sf::RectangleShape sfShape;
		CollisionBox collision;

		Box2D(std::string name, float width, float height, float mass);
		void SetPosition(Vector3D position) override;
		void Initialize() override;
		void PhysicsUpdate(sf::Time deltaTime) override;
	};
}


#endif


