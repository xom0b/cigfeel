#include "TextEntity.h"

TextEntity::TextEntity(sf::String text, sf::Vector2f position, TextStyle textStyle) : m_text(text), m_position(position), m_textStyle(textStyle)
{
	setPosition(position);
}

void TextEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Text text;
	text.setPosition(getPosition());
	text.setFont(m_textStyle.font);
	text.setFillColor(m_textStyle.color);
	text.setCharacterSize(m_textStyle.size);
	std::basic_string<sf::Uint32> unicode = { 0x16E0, 0x0020, 0x16E1, 0x0020, 0x16E2, 0x0020, 0x16E3, 0x0020, 0x16E4 };
	text.setString(unicode);
	
	target.draw(text);
}
