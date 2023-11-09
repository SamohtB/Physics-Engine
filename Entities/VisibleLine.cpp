#include "VisibleLine.h"

using namespace entity;

VisibleLine::VisibleLine(std::string name, Vector3D* startPoint, Vector3D* endPoint) : GameObject(name)
{
	this->startPoint = startPoint;
	this->endPoint = endPoint;
}

void VisibleLine::Initialize() {}

void VisibleLine::Draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
	GameObject::Draw(window, renderStates);
	sf::Vertex line[2];
	line[0].position = sf::Vector2f(this->startPoint->x, this->startPoint->y);
	line[1].position = sf::Vector2f(this->endPoint->x, this->endPoint->y);

	window->draw(line, 2, sf::Lines);
}



