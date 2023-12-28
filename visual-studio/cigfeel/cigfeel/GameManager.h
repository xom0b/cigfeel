#pragma once
#include<SFML/Graphics.hpp>
#include "GameState.h"

class GameManager
{
public:
	void Update(sf::RenderWindow& window, GameState& gameState);
};

