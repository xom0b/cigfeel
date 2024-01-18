#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LayoutMacros.h"
class DebugDrawer
{
	sf::Texture guideTexture;
	sf::IntRect guideRect;
	sf::Sprite guideSprite;
public:
	DebugDrawer();
	void draw(sf::RenderWindow& renderWindow);
};

