#include "TextHistory.h"
#include <iostream>
#include <windows.h>

TextHistory::TextHistory(size_t bufferSize, sf::Vector2f position, sf::Font& font, int textSpacing) 
	: m_currentIndex(0), 
	  m_bufferSize(bufferSize), 
	  m_inputBuffer(new std::string[bufferSize]),
	  m_textSpacing(textSpacing)
{
	setPosition(position);
	this->m_font = font;
}

TextHistory::~TextHistory()
{
	delete[] m_inputBuffer;
}

void TextHistory::submit()
{
	m_currentIndex = (m_currentIndex + 1) % (m_bufferSize - 1);
}

void TextHistory::append(std::string s)
{
	m_inputBuffer[m_currentIndex] += s;
}

void TextHistory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::Text text;
	text.setFont(m_font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(24);
	sf::Vector2f initialPosition = getPosition();

	int indexStep = m_currentIndex;
	for (size_t i = 0; i < m_bufferSize; i++)
	{
		text.setString(m_inputBuffer[i]);
		text.setPosition(initialPosition + sf::Vector2f(0, i * m_textSpacing));
		target.draw(text);
	}
}