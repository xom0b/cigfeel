#pragma once
#include <SFML/Graphics.hpp>
struct TextStyle
{
	sf::Font& font;
	sf::Color color;
	int size;

	TextStyle(sf::Font& font, sf::Color color, int size) : font(font), color(color), size(size){}
};