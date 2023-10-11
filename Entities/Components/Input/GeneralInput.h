#pragma once
#ifndef COMPONENT_GENERAL_INPUT_H
#define COMPONENT_GENERAL_INPUT_H

#include "../../../BaseClasses/Component.h"

namespace component
{
	using namespace baseclass;

	class GeneralInput : public Component
	{
	protected:
		sf::Event event;

	public:
		GeneralInput(std::string name);

		virtual void Perform() = 0;
		void AssignEvent(sf::Event event);
	};
}

#endif // !COMPONENT_GENERAL_INPUT_H



