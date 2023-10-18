#pragma once
#ifndef COMPONENT_EMISSION_CIRCLE_SHAPE_H
#define COMPONENT_EMISSION_CIRCLE_SHAPE_H

#include "ParticleSystem.h"

namespace component
{
	using namespace baseclass;

	class EmissionCircleShape : public Component 
	{
	public:
		EmissionCircleShape(std::string name, ParticleSystem* particleSystem);
		~EmissionCircleShape();
		void Perform();

	private:
		ParticleSystem* particleSystem;
		float angle;
	};
}

#endif // !COMPONENT_EMISSION_CIRCLE_SHAPE_H
