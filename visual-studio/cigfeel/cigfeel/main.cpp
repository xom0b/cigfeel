#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "GameDrawer.h"
#include "TextInputField.h"
#include "TextStyle.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");

    GameDrawer gameDrawer;
    sf::Font textFont;

    if (!textFont.loadFromFile("fonts\\Junicode-Regular.ttf"))
    {
        std::cout << "failed to load font" << std::endl;
    }
    else
    {
        std::cout << "loaded font" << std::endl;
    }

    int textSize = 24;
    sf::Color textColor = sf::Color::White;
    TextStyle textStyle(textFont, textColor, textSize);

    TextInputField textInputField(sf::Vector2f(240, 610), textStyle);

    int textHistoryBufferSize = 24;
    int textHistoryHorizontalSize = 24;
    TextHistory textHistory(textHistoryBufferSize, sf::Vector2f(240, 0), textStyle, textHistoryHorizontalSize);

    std::vector<sf::Drawable*> drawables;
    drawables.push_back(&textHistory);
    drawables.push_back(&textInputField);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.scancode == sf::Keyboard::Scan::Enter)
            {
                textHistory.append(textInputField.getInput());
                textHistory.submit();
                textInputField.clearInput();
            }
            else
            {
                textInputField.processEvent(event);
            }
        }

        gameDrawer.drawGame(window, drawables);
    }

    return 0;
}