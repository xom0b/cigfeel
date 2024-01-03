#pragma once
#include <string.h>
#include <SFML/Graphics.hpp>

class TextHistory : public sf::Drawable, public sf::Transformable
{
	size_t m_currentIndex;
	size_t m_bufferSize;
	std::string* m_inputBuffer;
	sf::Font m_font;
	int m_textSpacing;

public:
	TextHistory(size_t bufferSize, sf::Vector2f position, sf::Font &font, int textSpacing);
	~TextHistory();
	void submit();
	void append(std::string s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

