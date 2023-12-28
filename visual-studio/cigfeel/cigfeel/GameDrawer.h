#pragma once
#include <SFML/Graphics.hpp>
#include "TextHistory.h"
class GameDrawer
{
public:
	void drawGame(sf::RenderWindow& window, std::vector<sf::Drawable*>& drawables);
};

