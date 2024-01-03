#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "TextStyle.h"

class TextInputField : public sf::Drawable, public sf::Transformable
{
	std::string m_input;
	TextStyle m_textStyle;

public:
	TextInputField(sf::Vector2f position, TextStyle textStyle);
	void processEvent(sf::Event event);
	void clearInput();
	std::string getInput();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

