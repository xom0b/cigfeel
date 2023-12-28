#include "TextHistory.h"

TextHistory::TextHistory(size_t bufferSize) : m_bufferSize(bufferSize), m_currentIndex(0)
{
	m_inputBuffer = new sf::String[bufferSize];
}

TextHistory::~TextHistory()
{
	delete m_inputBuffer;
}

void TextHistory::submit()
{
	m_currentIndex = (m_currentIndex + 1) % (m_bufferSize - 1);
}

void TextHistory::append(sf::String s)
{
	m_inputBuffer[m_currentIndex] = m_inputBuffer[m_currentIndex] + s;
}

void TextHistory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}