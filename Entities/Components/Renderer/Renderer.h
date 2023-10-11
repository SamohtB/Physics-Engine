#pragma once
#ifndef COMPONENT_RENDERER_HPP
#define COMPONENT_RENDERER_HPP

#include "../../../BaseClasses/Component.h"

namespace component 
{
    using namespace baseclass;

    class Renderer : public Component 
    {
        public:
            Renderer(std::string name);

            void Perform();
            void Enable();
            void Disable();
            void Clear();

            void AssignTargetWindow(sf::RenderWindow* window);
            void AssignDrawable(sf::Drawable* drawable);
            
            sf::RenderStates GetRenderStates();
            void SetRenderStates(sf::RenderStates renderStates);

        private:
            bool isRendering;
            sf::RenderWindow* window;
            sf::Drawable* drawable;
            sf::RenderStates renderStates;
            
    };
}

#endif

