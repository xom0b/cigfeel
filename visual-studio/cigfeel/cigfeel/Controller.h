#pragma once
#include <SFML/Graphics.hpp>
class Controller
{
public:
	virtual void processEvent(sf::Event) = 0;
};

