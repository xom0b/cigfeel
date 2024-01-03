#include "TextInputField.h"
#include "TextUtils.h"
#include <SFML/System/Time.hpp>
#include <iostream>

TextInputField::TextInputField(sf::Vector2f position, TextStyle textStyle) : m_textStyle(textStyle), m_showCaret(true), m_elapsedCaretTime(sf::Time::Zero), m_caretBlinkDurationMilliseconds(530)
{
	setPosition(position);
}

void TextInputField::processEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.scancode == sf::Keyboard::Scan::Space)
		{
			m_input += " ";
		}
		else if (event.key.scancode == sf::Keyboard::Scan::Backspace)
		{
			if (m_input.size() > 0)
			{
				m_input.pop_back();
			}
		}
	}

	if (event.type == sf::Event::TextEntered)
	{
		if (IS_ASCII_LETTER(event.text.unicode)) // 32 is the ascii code for space
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

void TextInputField::update(sf::Time deltaTime)
{
	m_elapsedCaretTime += deltaTime;

	sf::Int32 elapsedMilliseconds = m_elapsedCaretTime.asMilliseconds();
	if (elapsedMilliseconds > m_caretBlinkDurationMilliseconds)
	{
		m_showCaret = !m_showCaret;

		sf::Int32 leftoverCaretTime = elapsedMilliseconds % m_caretBlinkDurationMilliseconds;
		m_elapsedCaretTime = sf::milliseconds(leftoverCaretTime);
	}
}

void TextInputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	// draw text
	sf::Text text;
	text.setPosition(getPosition());
	text.setFont(m_textStyle.font);
	text.setFillColor(m_textStyle.color);
	text.setCharacterSize(m_textStyle.size);
	text.setString(m_input + " ");
	target.draw(text);

	// draw caret
	if (m_showCaret)
	{
		text.setPosition(text.findCharacterPos(text.getString().getSize() - 1));
		text.setString("_");
		target.draw(text);
	}
}