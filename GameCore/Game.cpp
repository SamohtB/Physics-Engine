#include "Game.h"

using namespace gamecore;

Game::Game() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Engine by Banatin and Guzman", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);

    massAggregateSystem = new MassAggregateSystem();

    this->vectors.push_back(new Vector3D(0.0f, 500.0f, 0.0f));
	this->vectors.push_back(new Vector3D(SCREEN_WIDTH, 500.0f, 0.0f));

    VisibleLine* floor = new VisibleLine("Floor", vectors[0], vectors[1]);
    GameObjectManager::GetInstance()->AddObject(floor);

    AddCollidingParticles();
    AddAnchoredParticle();

}

void Game::AddCollidingParticles()
{
	ParticleObject* particle = new ParticleObject("Particle_1");

	GameObjectManager::GetInstance()->AddObject(particle);
	massAggregateSystem->AddParticle(particle->GetParticle());

    particle->SetRadius(10.0f);
	particle->SetPosition(Vector3D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));

	particle = new ParticleObject("Particle_2");
	GameObjectManager::GetInstance()->AddObject(particle);
	massAggregateSystem->AddParticle(particle->GetParticle());

    particle->SetRadius(10.0f);
	particle->SetPosition(Vector3D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 0));
}

void Game::AddAnchoredParticle()
{
	ParticleObject* particle = new ParticleObject("Anchored_Particle");
	GameObjectManager::GetInstance()->AddObject(particle);

    particle->SetRadius(10.0f);
    particle->SetPosition(Vector3D(SCREEN_WIDTH / 4, 300.0f, 0.0f));

	this->vectors.push_back(new Vector3D(SCREEN_WIDTH / 3, 250.0f, 0.0f));

	massAggregateSystem->AttachParticleToAnchoredSpring(particle->GetParticle(), this->vectors.back(), 0.5f, 75.0f);

	VisibleLine* line = new VisibleLine("AnchorLine", particle->GetParticle()->GetPositionReference(), this->vectors.back());
	GameObjectManager::GetInstance()->AddObject(line);
}

void Game::Run()
{
    sf::Clock clock = sf::Clock();
    sf::Time lastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.0f / FRAME_RATE_LIMIT);

    while(this->renderWindow.isOpen()) 
    {
        this->ProcessInput();
        lastUpdate += clock.restart();

        while(lastUpdate > timePerFrame) 
        {
            lastUpdate -= timePerFrame;
            this->Update(timePerFrame);
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
    massAggregateSystem->Update(deltaTime.asSeconds());
    GameObjectManager::GetInstance()->Update(deltaTime);
    GameObjectManager::GetInstance()->PhysicsUpdate(deltaTime);
}

void Game::Render()
{
    this->renderWindow.clear();

    GameObjectManager::GetInstance()->Draw(&this->renderWindow);

    this->renderWindow.display();
}