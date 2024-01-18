#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "TextStyle.h"
#include "TextBlock.h"
#include "LayoutMacros.h"

class TextHistory : public sf::Drawable, public sf::Transformable
{
	sf::FloatRect m_bounds;
	sf::Vector2f m_padding;
	TextStyle m_textStyle;
	int m_verticalSpacing;
	mutable std::vector<TextBlock> m_textBlocks;

public:
	TextHistory(sf::FloatRect bounds, sf::Vector2f padding, TextStyle textStyle, int verticalSpacing);
	void add(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

