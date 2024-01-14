#pragma once
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "TextStyle.h"

class TextHistory : public sf::Drawable, public sf::Transformable
{
	size_t m_currentIndex;
	size_t m_bufferSize;
	std::string* m_inputBuffer;
	TextStyle m_textStyle;
	int m_verticalSpacing;
	sf::IntRect m_rect;
	sf::Vector2i m_padding;

	int wrap(int step, int maxExclusive) const;
public:
	TextHistory(size_t bufferSize, sf::Vector2f position, TextStyle textStyle, int verticalSpacing, sf::IntRect rect, sf::Vector2i padding);
	~TextHistory();
	void submit();
	void append(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

