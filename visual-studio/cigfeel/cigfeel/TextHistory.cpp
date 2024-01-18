#include "TextHistory.h"

TextHistory::TextHistory(sf::FloatRect bounds, sf::Vector2f padding, TextStyle textStyle, int verticalSpacing) :
	m_bounds(bounds),
	m_padding(padding),
	m_textStyle(textStyle),
	m_verticalSpacing(verticalSpacing)
{
	setPosition(bounds.getPosition());
}

void TextHistory::add(std::string s)
{
	TextBlock textBlock(m_bounds.width, sf::Vector2f(TEXT_BLOCK_PADDING_X, TEXT_BLOCK_PADDING_Y), m_textStyle);
	textBlock.setString(s);
	m_textBlocks.push_back(textBlock);
}

void TextHistory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	float yPos = m_bounds.height - m_padding.y;
	float xPos = m_bounds.left;
	for (std::vector<TextBlock>::reverse_iterator block = m_textBlocks.rbegin(); block != m_textBlocks.rend(); block++)
	{
		float blockHeight = (*block).getBounds().height;
		yPos -= blockHeight;
		(*block).setPosition(sf::Vector2f(xPos, yPos));
		(*block).draw(target, states);
		yPos -= m_verticalSpacing;
	}
}