#include "TextBlock.h"

TextBlock::TextBlock(int width, sf::Vector2f padding, TextStyle textStyle) : m_width(width), m_padding(padding), m_textStyle(textStyle)
{
	m_text.setPosition(padding);
	m_bounds = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(width, 0));
	m_text.setFont(*textStyle.font);
	m_text.setCharacterSize(textStyle.size);
	m_text << textStyle.color;
}

void TextBlock::setString(std::string string)
{
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == '<')
		{
			if (i + 2 >= string.size())
			{
				std::cout << "formatting error in text block: improperly formatted tag" << std::endl;
				break;
			}

			char tag = string[i + 1];
			bool isClosed = tag == '/';
			if (isClosed)
			{
				tag = string[i + 2];
			}

			switch (tag)
			{
			case 'b':
				if (isClosed)
				{
					m_text >> sf::Text::Bold;
					i += 3;
				}
				else
				{
					m_text << sf::Text::Bold;
					i += 2;
				}
				break;
			case 'i':
				if (isClosed)
				{
					m_text >> sf::Text::Italic;
					i += 3;
				}
				else
				{
					m_text << sf::Text::Italic;
					i += 2;
				}
				break;
			case 'u':
				if (isClosed)
				{
					m_text >> sf::Text::Underlined;
					i += 3;
				}
				else
				{
					m_text << sf::Text::Underlined;
					i += 2;
				}
				break;
			case 'c':
				// =#AADDFF>
				if (i + 10 >= string.size())
				{
					std::cout << "formatting error in text block: color size error" << std::endl;
				}
				else
				{
					if (isClosed)
					{
						sf::Color defaultColor = m_textStyle.color;
						// TODO: set color
					}
					else
					{
						std::string colorString = string.substr(i + 3, 6);

						std::stringstream ss;
						ss << std::hex << colorString;
						unsigned int hexValue;
						ss >> hexValue;

						sf::Color newColor;
						newColor.r = (hexValue >> 16) & 0xFF;
						newColor.g = (hexValue >> 8) & 0xFF;
						newColor.b = hexValue & 0xFF;
						// TODO: set color

						i += 10;
					}
				}
				break;
			case 's':
				if (isClosed)
				{
					// TODO: set size back
				}
				else
				{
					int endIndex = string.substr(i).find_first_of('>');
					if (endIndex == std::string::npos)
					{
						std::cout << "formatting error in text block: couldn't determine size";
					}
					else
					{
						std::string number = string.substr(i + 2, endIndex - i + 2);
						int size = std::stoi(number);
						// set size
					}
					i = endIndex;
				}
				break;
			default:
				std::cout << "formatting error in text block: undefined formatter" << std::endl;
				break;
			}
		}
		else
		{
			m_text << string[i];
		}
	}

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
