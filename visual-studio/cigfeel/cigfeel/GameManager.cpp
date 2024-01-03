#include "GameManager.h"
#include <iostream>

void GameManager::updateGame(sf::RenderWindow& window, std::vector<Updateable*> updateables, std::vector<sf::Drawable*>& drawables, sf::Time deltaTime)
{
	for (size_t i = 0; i < updateables.size(); i++)
	{
		updateables[i]->update(deltaTime);
	}

	window.clear();

	for (size_t i = 0; i < drawables.size(); i++)
	{
		window.draw(*drawables[i]);
	}

	window.display();
}
