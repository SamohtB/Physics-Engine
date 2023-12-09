#include "Box2D.h"

#include <corecrt_math_defines.h>

using namespace entity;

Box2D::Box2D(std::string name, float width, float height, float mass) : GameObject(name)
{
	this->sfShape = sf::RectangleShape(sf::Vector2f(width, height));
	this->sfShape.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
	this->shape = RectShape2D(width, height);

	this->body.SetMass(mass);
	this->body.shape = &this->shape;
	this->collision.halfSize = Vector2D(width / 2.0f, height / 2.0f);
	this->collision.body = &(this->body);

	/*this->body.SetDamping(0.99f);
	this->body.angularDamping = 0.99f;*/
}

void Box2D::Initialize()
{
	Renderer* renderer = new Renderer(this->GetName() + "renderer");
	renderer->AssignDrawable(&this->sfShape);
	this->AttachComponent(renderer);
}


void Box2D::PhysicsUpdate(sf::Time deltaTime)
{
	GameObject::PhysicsUpdate(deltaTime);

	Vector2D pos = this->body.GetPosition();
	this->sfShape.setPosition(sf::Vector2f(pos.x, pos.y));
	this->sfShape.setRotation(this->body.rotation * 57.30f);

	sf::Transform transformMatrix = this->sfShape.getTransform();
	transformMatrix.translate(this->sfShape.getOrigin());
	this->body.transformMatrix = transformMatrix;
}


Vector2D Box2D::GetPosition2D()
{
	sf::Vector2f position2D = this->sprite->getPosition();

    return Vector2D(position2D.x, position2D.y);
}

void Box2D::SetPosition(Vector3D position)
{
	sf::Vector2f position2D = sf::Vector2f(position.x, position.y);
	this->sprite->setPosition(position2D);
	this->body.SetPosition(Vector2D(position.x, position.y));
}





