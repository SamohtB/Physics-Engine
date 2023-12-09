#include "Game.h"

using namespace gamecore;

Game::Game() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Engine by Banatin and Guzman", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);
    this->rigidbodySystem = new RigidbodySystem();

    Box2D* box = CreateBox("Box_1", Vector2D(SCREEN_WIDTH / 2.0f, 200.0f), false);
    //CreateBox("Box_2", Vector2D(SCREEN_WIDTH / 2.0f, 300.0f), false);

    box->body.AddForceOnPoint(Vector2D(25.0f, 0.0f), Vector2D(0, 50000.0f));
    box->body.SetDamping(0.99f);
    box->body.angularDamping = 1.0f;

    Vector3D* point = new Vector3D(0, 600.0f, 0);
    this->points.push_back(point);
    point = new Vector3D(SCREEN_WIDTH, 600.0f, 0);
    this->points.push_back(point);

    VisibleLine* line = new VisibleLine("Floor Line", points[0], points[1]);
    GameObjectManager::GetInstance()->AddObject(line);

}

Box2D* Game::CreateBox(std::string name, Vector2D initialPosition, bool hasGravity, float width, float height, float mass)
{
	Box2D* box = new Box2D(name, width, height, mass);
	GameObjectManager::GetInstance()->AddObject(box);

	this->rigidbodySystem->AddRigidbody(box, hasGravity);
	box->SetPosition(Vector3D(initialPosition.x, initialPosition.y, 0.0f));

    return box;
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
    this->rigidbodySystem->Update(deltaTime.asSeconds());
    GameObjectManager::GetInstance()->Update(deltaTime);
    GameObjectManager::GetInstance()->PhysicsUpdate(deltaTime);
}

void Game::Render()
{
    this->renderWindow.clear();

    GameObjectManager::GetInstance()->Draw(&this->renderWindow);

    this->renderWindow.display();
}