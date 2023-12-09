#pragma once
#ifndef GAMECORE_GAME_H
#define GAMECORE_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "../Config/Settings.h"
#include "../BaseClasses/EmptyGameObject.h"

#include "Managers/GameObjectManager.h"

#include "../Entities/Box2D.h"
#include "../Entities/VisibleLine.h"

#include "RigidbodySystem.h"

namespace gamecore
{
	using namespace baseclass;
	using namespace entity;
	using namespace singleton;
	using namespace physics;

	class Game
	{
	public:
		Box2D* CreateBox(std::string name, Vector2D initialPosition, bool hasGravity = true, float width = 50.0f, float height = 50.0f, float mass = 10.0f);
		void AddBoxesAttachedBySpring();
		Game();

		void Run();
		void ProcessInput();
		void Update(sf::Time deltaTime);
		void DrawFloor();
		void DrawSpringLine();
		void Render();

	private:
		sf::RenderWindow renderWindow;
		RigidbodySystem* rigidbodySystem;

		Box2D* spring_box_1;
		Box2D* spring_box_2;

	};
}

#endif


