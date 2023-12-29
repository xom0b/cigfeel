#include "TextHistory.h"
#include <iostream>
#include <windows.h>

TextHistory::TextHistory(size_t bufferSize, sf::Vector2f position, sf::Font& font) 
	: m_currentIndex(0), 
	  m_bufferSize(bufferSize), 
	  m_inputBuffer(new std::string[bufferSize])
{
	setPosition(position);
	this->font = font;
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

	std::string output = "";
	output += m_inputBuffer[m_currentIndex] + "\n";

	int indexStep = m_currentIndex;
	for (size_t i = 0; i < m_bufferSize; i++)
	{
		output += m_inputBuffer[i] + "\n";
	}

	sf::Text text;
	text.setPosition(getPosition());
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(24);
	text.setString(output);
	target.draw(text);
}