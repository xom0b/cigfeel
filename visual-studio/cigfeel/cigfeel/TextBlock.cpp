#include "TextBlock.h"

TextBlock::TextBlock(int width, sf::Vector2f padding, TextStyle textStyle) : m_width(width), m_padding(padding), m_defaultStyle(textStyle)
{
	m_text.setPosition(padding);
	m_bounds = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(width, 0));
	m_text.setFont(*textStyle.font);
	m_text.setCharacterSize(textStyle.size);
	m_text << textStyle.color;
}

void TextBlock::setString(std::string string)
{
	m_text << string;
	m_bounds = m_text.getGlobalBounds();
}

sf::FloatRect TextBlock::getBounds()
{
	return m_bounds;
}

void TextBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_text, states);
}
