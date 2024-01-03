#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Updatable.h"
class GameManager
{
public:
	void updateGame(sf::RenderWindow& window, std::vector<Updateable*> updateables, std::vector<sf::Drawable*>& drawables, sf::Time deltaTime);
};

