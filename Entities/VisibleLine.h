#pragma once
#ifndef ENTITY_VISIBLE_LINE_H
#define ENTITY_VISIBLE_LINE_H

#include "../BaseClasses/GameObject.h"
#include "Components/Renderer/Renderer.h"
#include "../BaseClasses/Vector2D.h"

namespace entity
{
	using namespace baseclass;
	using namespace component;

	class VisibleLine :	public GameObject
	{
	public:
		VisibleLine(std::string name, Vector3D* startPoint, Vector3D* endPoint);
		void Initialize() override;
		void Draw(sf::RenderWindow* window, sf::RenderStates renderStates) override;

	private:
		Vector3D* startPoint;
		Vector3D* endPoint;
	};

	class VisibleLine2D :	public GameObject
	{
	public:
		VisibleLine2D(std::string name, Vector2D* startPoint, Vector2D* endPoint);
		void Initialize() override;
		void Draw(sf::RenderWindow* window, sf::RenderStates renderStates) override;

	private:
		Vector2D* startPoint;
		Vector2D* endPoint;
	};
}

#endif



