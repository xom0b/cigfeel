#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>

class TextInputField : public sf::Drawable, public sf::Transformable
{
	sf::Font m_font;
	std::string m_input;
	sf::Color m_color;
	int m_size;
public:
	TextInputField(sf::Vector2f position, sf::Font& font, sf::Color color, int size);
	void processEvent(sf::Event event);
	void clearInput();
	std::string getInput();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

