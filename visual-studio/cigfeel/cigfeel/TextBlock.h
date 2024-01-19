#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

#include "TextStyle.h"
#include "RichText.h"
class TextBlock : public sf::Drawable, public sf::Transformable
{
	int m_width;
	sf::FloatRect m_bounds;
	sf::Vector2f m_padding;
	TextStyle m_textStyle;
	sfe::RichText m_text;
public:
	TextBlock(int width, sf::Vector2f m_padding, TextStyle textStyle);
	void setString(std::string string);
	sf::FloatRect getBounds();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

