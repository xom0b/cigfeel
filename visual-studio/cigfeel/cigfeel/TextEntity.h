#pragma once
#include <SFML/Graphics.hpp>
#include "TextStyle.h"
class TextEntity : public sf::Drawable, public sf::Transformable
{
	sf::String m_text;
	sf::Vector2f m_position;
	TextStyle m_textStyle;
public:
	TextEntity(sf::String text, sf::Vector2f position, TextStyle textStyle);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

