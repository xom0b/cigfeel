#pragma once
#include <string.h>
#include <SFML/Graphics.hpp>
#include "TextStyle.h"

class TextHistory : public sf::Drawable, public sf::Transformable
{
	size_t m_currentIndex;
	size_t m_bufferSize;
	std::string* m_inputBuffer;
	TextStyle m_textStyle;
	int m_horizontalSpacing;

public:
	TextHistory(size_t bufferSize, sf::Vector2f position, TextStyle textStyle, int horizontalSpacing);
	~TextHistory();
	void submit();
	void append(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

