#include "GeneralInput.h"

using namespace component;

GeneralInput::GeneralInput(std::string name) : Component(name, ComponentType::INPUT) {}

void GeneralInput::AssignEvent(sf::Event event)
{
	this->event = event;
}