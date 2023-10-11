#pragma once
#ifndef GAMECORE_GAME_H
#define GAMECORE_GAME_H

#include <vector>
#include <iomanip>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "../Config/Settings.h"
#include "../BaseClasses//Vector3D.h"
#include "Managers/GameObjectManager.h"
#include "../Entities/ParticleObject.h"

#include "../Physics/Particles/ParticleForceRegistry.h"
#include "../Physics/Particles/ParticleSpring.h"
#include "../Physics/Particles/ParticleDrag.h"
#include "../Physics/Particles/ParticleAnchoredSpring.h"

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

		~Game() = default;

		void Run();
		void ProcessInput();
		void Update(sf::Time deltaTime);
		void Render();

	private:
		sf::RenderWindow renderWindow;
		ParticleForceRegistry* registry;
	};
}

#endif


