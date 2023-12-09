#include "Shape2D.h"

using namespace physics;

float RectShape2D::GetInertiaTensor(float mass)
{
	return mass * (this->width * this->width + this->height * this->height) / 12.0f;
}

float CircleShape2D::GetInertiaTensor(float mass)
{
	return mass * this->radius * this->radius * 0.4f;
}
