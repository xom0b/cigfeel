#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
class GameDrawer
{
public:
	void DrawGame(sf::RenderWindow& window, GameState& gameState);
};

