#include "Game.h"

using namespace gamecore;

Game::Game() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Engine by Banatin and Guzman", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);
    this->registry = new ParticleForceRegistry();

    EmptyGameObject* systemBody = new EmptyGameObject("GameObject Test");
    GameObjectManager::GetInstance()->AddObject(systemBody);
    systemBody->SetPosition(Vector3D(500.0f, 500.0f, 0.0f));

    ParticleSystem* particleSystem = new ParticleSystem("Particle System");
    systemBody->AttachComponent(particleSystem);

    particleSystem->SetGravity(Vector3D(0.0f, 200.0f, 0.0f));
    particleSystem->SetEmissionVector(Vector3D(300.0f, -1000.0f, 0.0f));
    particleSystem->SetEmissionRate(10.f);
    particleSystem->SetLifeTime(3.5f);

    particleSystem->Initialize();
}

void Game::Run()
{
    sf::Clock CClock = sf::Clock();
    sf::Time tLastUpdate = sf::Time::Zero;
    sf::Time tTimePerFrame = sf::seconds(1.0f / FRAME_RATE_LIMIT);

    while(this->renderWindow.isOpen()) 
    {
        this->ProcessInput();
        tLastUpdate += CClock.restart();

        while(tLastUpdate > tTimePerFrame) 
        {
            tLastUpdate -= tTimePerFrame;
            this->Update(tTimePerFrame);
        }

        this->Render();
    }
}

void Game::ProcessInput()
{
    sf::Event eEvent;

    while(this->renderWindow.pollEvent(eEvent)) 
    {
        switch(eEvent.type) 
        {
            case sf::Event::Closed:
                this->renderWindow.close();
                break;

            default:
                GameObjectManager::GetInstance()->ProcessInput(eEvent);
                break;
        }
    }
}

void Game::Update(sf::Time deltaTime)
{
    GameObjectManager::GetInstance()->Update(deltaTime);
    GameObjectManager::GetInstance()->PhysicsUpdate(deltaTime);
}

void Game::Render()
{
    this->renderWindow.clear();

    GameObjectManager::GetInstance()->Draw(&this->renderWindow);

    this->renderWindow.display();
}