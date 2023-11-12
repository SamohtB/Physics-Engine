#pragma once
#ifndef GAMECORE_GAME_H
#define GAMECORE_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "../Config/Settings.h"
#include "../BaseClasses/EmptyGameObject.h"

#include "Managers/GameObjectManager.h"

#include "../Entities/ParticleObject.h"
#include "../Entities/VisibleLine.h"

#include "MassAggregateSystem.h"

namespace gamecore
{
	using namespace baseclass;
	using namespace entity;
	using namespace singleton;
	using namespace physics;

	class Game
	{
	public:
		void AddCollidingParticles();
		void AttachParticleToParticleRod();
		void AttachParticleToParticleSpring();
		void AttachParticleToAnchoredSpring();
		void AttachParticleToAnchoredCable();
		Game();

		void Run();
		void ProcessInput();
		void Update(sf::Time deltaTime);
		void Render();

	private:
		sf::RenderWindow renderWindow;
		MassAggregateSystem* massAggregateSystem;
		std::vector<Vector3D*> vectors;
	};
}

#endif


