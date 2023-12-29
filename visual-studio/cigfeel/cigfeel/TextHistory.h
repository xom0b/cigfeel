#pragma once
#include <string.h>
#include <SFML/Graphics.hpp>

class TextHistory : public sf::Drawable
{
	size_t m_currentIndex;
	size_t m_bufferSize;
	sf::Font font;
	std::string * m_inputBuffer;

public:
	TextHistory(size_t bufferSize);
	~TextHistory();
	void submit();
	void append(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

