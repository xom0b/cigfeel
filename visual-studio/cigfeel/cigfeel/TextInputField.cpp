#include "TextInputField.h"
#include <iostream>

TextInputField::TextInputField(sf::Vector2f position, sf::Font& font, sf::Color color, int size) : m_font(font), m_color(color), m_size(size)
{
	setPosition(position);
}

void TextInputField::processEvent(sf::Event event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			m_input += event.text.unicode;
		}
	}
}

void TextInputField::clearInput()
{
	m_input = "";
}

std::string TextInputField::getInput()
{
	return m_input;
}

void TextInputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Text text;
	text.setPosition(getPosition());
	text.setFont(m_font);
	text.setFillColor(m_color);
	text.setCharacterSize(m_size);
	text.setString(m_input);
	target.draw(text);
}
