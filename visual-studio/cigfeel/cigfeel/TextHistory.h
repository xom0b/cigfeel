#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

class TextHistory : public sf::Drawable
{
	size_t m_currentIndex;
	size_t m_bufferSize;
	sf::String  * m_inputBuffer;

public:
	TextHistory(size_t bufferSize);
	~TextHistory();
	void submit();
	void append(sf::String s);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

