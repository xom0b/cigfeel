#include "TextHistory.h"
#include <iostream>
#include <windows.h>

TextHistory::TextHistory(size_t bufferSize) : m_bufferSize(bufferSize), m_currentIndex(0)
{
	m_inputBuffer = new std::string[bufferSize];
	if (!font.loadFromFile("fonts\\Junicode-Regular.ttf"))
	{
		std::cout << "failed to load font" << std::endl;
	}
	else
	{
		std::cout << "loaded font" << std::endl;
	}
}

TextHistory::~TextHistory()
{
	delete m_inputBuffer;
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
	std::string output = "";
	int indexStep = m_currentIndex;
	for (size_t i = m_bufferSize - 1; i >= 0; i--)
	{
		output += (m_inputBuffer[i] + "\n");
		i = (i + 1) % m_bufferSize;
	}

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(16);
	text.setString(output);
}