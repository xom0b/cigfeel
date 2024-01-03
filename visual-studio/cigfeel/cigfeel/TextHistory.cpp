#include "TextHistory.h"
#include <iostream>
#include <windows.h>

TextHistory::TextHistory(size_t bufferSize, sf::Vector2f position, TextStyle textStyle, int verticalSpacing) 
	: m_currentIndex(0), 
	  m_bufferSize(bufferSize), 
	  m_inputBuffer(new std::string[bufferSize]),
	  m_textStyle(textStyle),
	  m_verticalSpacing(verticalSpacing)
{
	setPosition(position);
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
	text.setFont(m_textStyle.font);
	text.setFillColor(m_textStyle.color);
	text.setCharacterSize(m_textStyle.size);
	sf::Vector2f initialPosition = getPosition();
	int totalHeight = m_verticalSpacing * m_bufferSize;

	int indexStep = m_currentIndex;
	for (size_t i = 0; i < m_bufferSize; i++)
	{
		text.setString(m_inputBuffer[indexStep]);
		text.setPosition(initialPosition + sf::Vector2f(0, i * m_verticalSpacing));
		target.draw(text);

		indexStep = (indexStep + 1) % m_bufferSize;
	}
}