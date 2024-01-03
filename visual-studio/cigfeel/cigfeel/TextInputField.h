#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "TextStyle.h"
#include "Updatable.h"

class TextInputField : public sf::Drawable, public sf::Transformable, public Updateable
{
	std::string m_input;
	TextStyle m_textStyle;
	bool m_showCaret;
	sf::Time m_elapsedCaretTime;
	int m_caretBlinkDurationMilliseconds;

public:
	TextInputField(sf::Vector2f position, TextStyle textStyle);
	void processEvent(sf::Event event);
	void clearInput();
	std::string getInput();
	void update(sf::Time time);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

