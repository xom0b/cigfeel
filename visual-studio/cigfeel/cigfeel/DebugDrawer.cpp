#include "DebugDrawer.h"

DebugDrawer::DebugDrawer()
{
	if (!guideTexture.loadFromFile("textures/layout-guides-720.png"))
	{
		std::cout << "failed to load guide texture" << std::endl;
	}

	guideRect = sf::IntRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	guideSprite.setTexture(guideTexture);
	guideSprite.setPosition(sf::Vector2f(100, 0));
}

void DebugDrawer::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(guideSprite);
}
