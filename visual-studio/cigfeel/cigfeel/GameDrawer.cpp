#include "GameDrawer.h"
#include <iostream>

void GameDrawer::drawGame(sf::RenderWindow& window, std::vector<sf::Drawable*>& drawables)
{
	window.clear();
	
	for (size_t i = 0; i < drawables.size(); i++)
	{
		window.draw(*drawables[i]);
	}
	
	window.display();
}
