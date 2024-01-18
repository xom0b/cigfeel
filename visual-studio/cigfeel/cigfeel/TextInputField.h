#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "TextStyle.h"
#include "Updatable.h"

class TextInputField : public sf::Drawable, public sf::Transformable, public Updateable
{
	mutable sf::Text m_text;
	std::string m_input;
	TextStyle m_textStyle;
	bool m_showCaret;
	sf::Time m_elapsedCaretTime;
	int m_caretBlinkDurationMilliseconds;
	sf::IntRect m_rect;
	sf::Vector2i m_padding;

public:
	TextInputField(sf::IntRect rect, sf::Vector2i padding, TextStyle textStyle);
	void processEvent(sf::Event event);
	void clearInput();
	std::string getInput();
	void update(sf::Time time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

