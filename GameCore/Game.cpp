#include "Game.h"

using namespace gamecore;

Game::Game() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Engine by Banatin and Guzman", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);
    this->rigidbodySystem = new RigidbodySystem();

    spring_box_1 =  CreateBox("Box_1", Vector2D(SCREEN_WIDTH / 2.0f, 200.0f), false);
    spring_box_2 =  CreateBox("Box_2", Vector2D(SCREEN_WIDTH / 2.0f, 300.0f));

    Vector2D localPointA = Vector2D(25.0f, 0.0f);
    Vector2D localPointB = Vector2D(0.0f, -25.0f);

    this->rigidbodySystem->AttachBoxToBox(
        spring_box_1,
        localPointA, 
        spring_box_2, 
        localPointB, 
        70.0f, 
        60.0f);
    
    AddFloor();
}

Box2D* Game::CreateBox(std::string name, Vector2D initialPosition, bool hasGravity, float width, float height, float mass)
{
	Box2D* box = new Box2D(name, width, height, mass);
	GameObjectManager::GetInstance()->AddObject(box);

	this->rigidbodySystem->AddRigidbody(box, hasGravity);

	box->SetPosition(Vector3D(initialPosition.x, initialPosition.y, 0.0f));
    box->body.SetDamping(0.99f);
    box->body.angularDamping = 1.0f;

    return box;
}

void Game::AddFloor()
{
	Vector2D* pointA = new Vector2D(0, 600.0f);
	this->points.push_back(pointA);
	Vector2D* pointB = new Vector2D(SCREEN_WIDTH, 600.0f);
	this->points.push_back(pointB);

	VisibleLine2D* line = new VisibleLine2D("Floor Line", pointA, pointB);
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
    this->rigidbodySystem->Update(deltaTime.asSeconds());
    GameObjectManager::GetInstance()->Update(deltaTime);
    GameObjectManager::GetInstance()->PhysicsUpdate(deltaTime);
}

void Game::Render()
{
    this->renderWindow.clear();

    sf::Vertex springLine[] =  {
    	sf::Vertex(spring_box_1->body.transformMatrix.transformPoint(sf::Vector2f(25.0f, 0.0f)), sf::Color::Red), 
		sf::Vertex(spring_box_2->body.transformMatrix.transformPoint(sf::Vector2f(0.0f, -25.0f)), sf::Color::Red)
    };

    renderWindow.draw(springLine, 2, sf::Lines);

    GameObjectManager::GetInstance()->Draw(&this->renderWindow);

    this->renderWindow.display();
}