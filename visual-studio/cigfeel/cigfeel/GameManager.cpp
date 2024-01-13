#include "GameManager.h"
#include <iostream>

void GameManager::input(std::vector<Controller*>& controllers, sf::Event event)
{
	for (Controller* controller : controllers)
	{
		controller->processEvent(event);
	}
}

void GameManager::update(std::vector<Updateable*>& updateables, sf::Time deltaTime)
{
	for (Updateable* updateable : updateables)
	{
		updateable->update(deltaTime);
	}
}

void GameManager::draw(std::vector<sf::Drawable*>& drawables, sf::RenderWindow& window)
{
	for (sf::Drawable* drawable : drawables)
	{
		window.draw(*drawable);
	}
}
