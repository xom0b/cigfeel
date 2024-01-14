#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "TextStyle.h"

class TextHistory : public sf::Drawable, public sf::Transformable
{
	mutable sf::Text m_text;
	size_t m_currentIndex;
	size_t m_bufferSize;
	std::string* m_inputBuffer;
	TextStyle m_textStyle;
	int m_verticalSpacing;
	sf::IntRect m_rect;
	sf::Vector2i m_padding;

	int wrap(int step, int maxExclusive) const;
	std::vector<std::string> splitToLines(std::string string, int maxWidth) const;
public:
	TextHistory(size_t bufferSize, sf::Vector2f position, TextStyle textStyle, int verticalSpacing, sf::IntRect rect, sf::Vector2i padding);
	~TextHistory();
	void add(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

