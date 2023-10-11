#include "GameObjectManager.h"

using namespace singleton;

void GameObjectManager::ProcessInput(sf::Event event)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->ProcessInput(event);
    }
}

void GameObjectManager::Update(sf::Time deltaTime)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->Update(deltaTime);
    }
}

void GameObjectManager::PhysicsUpdate(sf::Time deltaTime)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->PhysicsUpdate(deltaTime);
    }
}

void GameObjectManager::Draw(sf::RenderWindow* window)
{
    for(GameObject* gameObject : this->gameObjectList)
    {
        gameObject->Draw(window, sf::RenderStates::Default);
    }
}

void GameObjectManager::AddObject(GameObject* gameObject)
{
    this->gameObjectList.push_back(gameObject);
    gameObject->Initialize();
}

GameObjectManager* GameObjectManager::Instance = NULL;

GameObjectManager* GameObjectManager::GetInstance()
{
    if(Instance == NULL)
        Instance = new GameObjectManager();

    return Instance;
}