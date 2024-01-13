#pragma once
#include<SFML/System/Time.hpp>
class Updateable
{
public:
	virtual void update(sf::Time deltaTime) = 0;
};