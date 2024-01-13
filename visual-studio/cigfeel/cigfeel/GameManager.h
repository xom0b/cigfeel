#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Updatable.h"
#include "Controller.h"
class GameManager
{
public:
	void input(std::vector<Controller*>& controllers, sf::Event event);
	void update(std::vector<Updateable*>& updateables, sf::Time deltaTime);
	void draw(std::vector<sf::Drawable*>& drawables, sf::RenderWindow& window);
};

