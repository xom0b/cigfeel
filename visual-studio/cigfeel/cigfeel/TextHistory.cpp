#include "TextHistory.h"

TextHistory::TextHistory(size_t bufferSize, sf::Vector2f position, TextStyle textStyle, int verticalSpacing, sf::IntRect rect, sf::Vector2i padding) 
	: m_currentIndex(0), 
	  m_bufferSize(bufferSize), 
	  m_inputBuffer(new std::string[bufferSize]),
	  m_textStyle(textStyle),
	  m_verticalSpacing(verticalSpacing),
	  m_rect(rect),
	  m_padding(padding)
{
	setPosition(position); 
}

TextHistory::~TextHistory()
{
	delete[] m_inputBuffer;
}

void TextHistory::submit()
{
	m_currentIndex = (m_currentIndex + 1) % (m_bufferSize);
}

void TextHistory::append(std::string s)
{
	m_inputBuffer[m_currentIndex] = s;
}

void TextHistory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	sf::Text text;
	text.setFont(*m_textStyle.font);
	text.setFillColor(m_textStyle.color);
	text.setCharacterSize(m_textStyle.size);
	int initialY = m_rect.height - (m_textStyle.size + m_verticalSpacing) - m_padding.y;
	int initialX = getPosition().x;

	int indexStep = wrap(m_currentIndex, m_bufferSize);
	for (int i = 0; i < m_bufferSize; i++)
	{
		text.setString(m_inputBuffer[indexStep]);

		sf::Vector2f position(initialX, initialY - i * (m_textStyle.size + m_verticalSpacing));
		text.setPosition(position);
		
		target.draw(text);

		indexStep = wrap(indexStep, m_bufferSize);
	}
}

int TextHistory::wrap(int step, int maxExclusive) const
{
	int decremented = step - 1;

	if (decremented < 0)
	{
		decremented = maxExclusive - 1;
	}

	return decremented;
}