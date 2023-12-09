#include "Game.h"

using namespace gamecore;

Game::Game() : renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Engine by Banatin and Guzman", sf::Style::Titlebar | sf::Style::Close)
{
	this->renderWindow.setFramerateLimit(FRAME_RATE_LIMIT);
    this->rigidbodySystem = new RigidbodySystem(Vector2D(0, 98.0f), 128, 0.8f);

    spring_box_1 = nullptr;
    spring_box_2 = nullptr;

    AddBoxesAttachedBySpring();
    //CreateBox("Box_Test_1", Vector2D(230, 50.0f));
    //CreateBox("Box_Test_2", Vector2D(230, 200.0f));
    //CreateBox("Box_Test_3", Vector2D(215, 350.0f));
    
    CreateBox("Box_Test_4", Vector2D(725, 200.0f));
    Box2D* box = CreateBox("Box_Test_5", Vector2D(715, 50.0f));
    box->body.AddForceOnPoint(Vector2D(25.0f, 0.0f), Vector2D(0.0f, 50000.0f));

    this->rigidbodySystem->Initialize();
}

Box2D* Game::CreateBox(std::string name, Vector2D initialPosition, bool hasGravity, float width, float height, float mass)
{
	Box2D* box = new Box2D(name, width, height, mass);
	GameObjectManager::GetInstance()->AddObject(box);

	box->SetPosition(Vector3D(initialPosition.x, initialPosition.y, 0.0f));
	this->rigidbodySystem->AddRigidbody(box, hasGravity);

    return box;
}

void Game::AddBoxesAttachedBySpring()
{
	spring_box_1 = CreateBox("Box_1", Vector2D(SCREEN_WIDTH / 2.0f, 100.0f), true, 50.0f, 50.0f, 10.0f);
	spring_box_2 = CreateBox("Box_2", Vector2D(SCREEN_WIDTH / 2.0f, 300.0f), true, 50.0f, 50.0f, 10.0f);

	Vector2D localPointA = Vector2D(12.5f, 0.0f);
	Vector2D localPointB = Vector2D(0.0f, 25.0f);

	this->rigidbodySystem->AttachBoxToBox(
		spring_box_1,
		localPointA, 
		spring_box_2, 
		localPointB, 
		70.0f, 
		60.0f);
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

    DrawFloor();
    GameObjectManager::GetInstance()->Draw(&this->renderWindow);
    DrawSpringLine();

    this->renderWindow.display();
}

void Game::DrawSpringLine()
{
	sf::Vertex springLine[] =  {
		sf::Vertex(spring_box_1->body.transformMatrix.transformPoint(sf::Vector2f(25.0f, 0.0f)), sf::Color::Red), 
		sf::Vertex(spring_box_2->body.transformMatrix.transformPoint(sf::Vector2f(0.0f, -25.0f)), sf::Color::Red)
	};

	renderWindow.draw(springLine, 2, sf::Lines);
}

void Game::DrawFloor()
{
	sf::Vertex springLine[] =  {
		sf::Vertex(sf::Vector2f(0.0f, 500.0f), sf::Color::White), 
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH, 500.0f), sf::Color::White)
	};

	renderWindow.draw(springLine, 2, sf::Lines);
}
