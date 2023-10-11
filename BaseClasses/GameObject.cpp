#include "GameObject.h"

using namespace baseclass;

GameObject::GameObject(std::string name)
{
    this->isEnabled = true;
    this->name = name;
	this->sprite = new sf::Sprite();
    this->sprite->setOrigin(0.0f, 0.0f);
    this->sprite->setPosition(0.0f, 0.0f);
	this->componentList = {};
}

void GameObject::ProcessInput(sf::Event event)
{
    std::vector<Component*> inputComponentList = this->GetComponents(ComponentType::INPUT);
    GeneralInput* generalInput;

    for(Component* component : inputComponentList) 
    {
        if(component->GetOwner()->GetEnabledStatus()) 
        {
            generalInput = (GeneralInput*)component;
            generalInput->AssignEvent(event);
            generalInput->Perform();
        }
    }
}

void GameObject::Update(sf::Time deltaTime)
{
    std::vector<Component*> scriptComponentList = this->GetComponents(ComponentType::SCRIPT);
    
    for(Component* component : scriptComponentList) 
    {
        if(component->GetOwner()->GetEnabledStatus()) 
        {
            component->SetDeltaTime(deltaTime);
            component->Perform();
        }
    }
}

void GameObject::PhysicsUpdate(sf::Time deltaTime) 
{
    std::vector<Component*> physicsComponentList = this->GetComponents(ComponentType::PHYSICS);
    
    for(Component* component : physicsComponentList) 
    {
        if(component->GetOwner()->GetEnabledStatus()) 
        {
            component->SetDeltaTime(deltaTime);
            component->Perform();
        }
    }
}

void GameObject::Draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
    sf::RenderStates transformedRenderStates(renderStates);
    transformedRenderStates.transform = this->sprite->getTransform() * transformedRenderStates.transform;

    std::vector<Component*> rendererComponentList = this->GetComponents(ComponentType::RENDERER);
    Renderer* renderer;

	for (Component* component : rendererComponentList)
	{
		renderer = (Renderer*)component;
		renderer->AssignTargetWindow(window);
		renderer->SetRenderStates(renderStates);
		renderer->Perform();
	}
}

void GameObject::AttachComponent(Component* component)
{
    this->componentList.push_back(component);
    component->AttachOwner(this);
}

void GameObject::DetachComponent(Component* component)
{
    int index = -1;
    for(int i = 0; i < this->componentList.size() && index == -1; i++) 
    {
        if(this->componentList[i] == component) 
        {
            index = i;
        }
    }

    if(index != -1) 
    {
        this->componentList[index]->DetachOwner();
        this->componentList.erase(this->componentList.begin() + index);
    }
}

Component* GameObject::FindComponentByName(std::string name)
{
    for(Component* component : this->componentList) 
    {
        if(component->GetName() == name)
        {
             return component;
        }
    }
    
    std::cout << "[ERROR] : Component [" << name << "] NOT found." << std::endl;
    return NULL;
}

std::vector<Component*> GameObject::GetComponents(ComponentType componentType)
{
    std::vector<Component*> found = {};

    for(Component* component : this->componentList) 
    {
        if(component->GetType() == componentType)
        {
            found.push_back(component);
        }
    }

    return found;
}

Vector3D GameObject::GetPosition()
{
    sf::Vector2f position2D = this->sprite->getPosition();

    return Vector3D(position2D.x, position2D.y, 0.0f);
}

void GameObject::SetPosition(Vector3D position)
{
    this->sprite->setPosition(position.x, position.y);
}

void GameObject::Move(Vector3D displacement)
{
    sf::Vector2f position2D = this->sprite->getPosition();
    Vector3D position3D(position2D.x, position2D.y, 0.0f);

    this->SetPosition(Vector3D(position3D + displacement));
}

std::string GameObject::GetName()
{
	return this->name;
}

sf::Sprite* GameObject::GetSprite()
{
	return this->sprite;
}

bool GameObject::GetEnabledStatus()
{
	return this->isEnabled;
}

void GameObject::SetEnabledStatus(bool status)
{
	this->isEnabled = status;
}