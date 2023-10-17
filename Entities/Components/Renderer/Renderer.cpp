#include "Renderer.h"

using namespace component;

Renderer::Renderer(std::string strName) : Component(strName, ComponentType::RENDERER) 
{
    this->isRendering = true;
    this->renderStates = sf::RenderStates::Default;
    this->drawable = NULL;
}

void Renderer::Perform()
{
    if(this->isRendering)
    {
        this->window->draw(*this->drawable, this->renderStates);
    }
}

void Renderer::Enable()
{
	this->isRendering = true;
}

void Renderer::Disable()
{
	this->isRendering = false;
}

void Renderer::Clear()
{
	this->drawable = nullptr;
}

void Renderer::AssignTargetWindow(sf::RenderWindow* window) 
{
    this->window = window;
}

void Renderer::AssignDrawable(sf::Drawable* drawable) 
{
    this->drawable = drawable;
}

void Renderer::SetRenderStates(sf::RenderStates renderStates) 
{
    this->renderStates = renderStates;
}

sf::RenderStates Renderer::GetRenderStates() 
{
    return this->renderStates;
}