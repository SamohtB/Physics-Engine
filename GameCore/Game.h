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
		Game();

		void Run();
		void ProcessInput();
		void Update(sf::Time deltaTime);
		void Render();

	private:
		sf::RenderWindow renderWindow;
		RigidbodySystem* rigidbodySystem;

	};
}

#endif


