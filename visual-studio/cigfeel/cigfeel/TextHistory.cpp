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

	m_text.setFont(*m_textStyle.font);
	m_text.setFillColor(m_textStyle.color);
	m_text.setCharacterSize(m_textStyle.size);
}

TextHistory::~TextHistory()
{
	delete[] m_inputBuffer;
}

void TextHistory::add(std::string s)
{
	std::vector<std::string> sWithNewLines = splitToLines(s, 100);

	for (std::string sWithNewLine : sWithNewLines)
	{
		m_inputBuffer[m_currentIndex] = sWithNewLine;
		m_currentIndex = (m_currentIndex + 1) % (m_bufferSize);
	}
}

void TextHistory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	int yPosStep = m_rect.height - m_padding.y;
	int xPosStep = getPosition().x;

	int indexStep = wrap(m_currentIndex, m_bufferSize);
	for (int i = 0; i < m_bufferSize; i++)
	{
		std::string line = m_inputBuffer[indexStep];
		m_text.setString(line);

		yPosStep -= m_verticalSpacing;

		sf::Vector2f position(xPosStep, yPosStep);
		m_text.setPosition(position);
		
		target.draw(m_text);

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

std::vector<std::string> TextHistory::splitToLines(std::string string, int maxWidth) const
{
	std::vector<std::string> stringLines;
	int maxWidthStep = m_rect.left + maxWidth;
	m_text.setString(string);

	int cutIndex = 0;
	for (size_t i = 0; i < string.length(); i++)
	{
		int currentCharacterPos = m_text.findCharacterPos(i).x;
		if (currentCharacterPos > maxWidthStep)
		{
			int spaceIndex = string.substr(0, i).find_last_of(" ");

			if (spaceIndex >= 0)
			{
				string[spaceIndex] = '\n';
				cutIndex = spaceIndex + 1;

				int positionOffset = currentCharacterPos - m_text.findCharacterPos(spaceIndex).x;
				maxWidthStep -= positionOffset;
			}
			else
			{
				string.insert(i - 1, "-\n");
				cutIndex = i + 1;
			}

			maxWidthStep += maxWidth;
		}
	}

	
	std::istringstream stream(string);
	std::string token;

	while (std::getline(stream, token))
	{
		stringLines.push_back(token);
	}

	return stringLines;
}