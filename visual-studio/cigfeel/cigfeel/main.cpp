#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "GameManager.h"
#include "TextInputField.h"
#include "TextHistory.h"
#include "TextStyle.h"
#include "TextEntity.h"
#include "Updatable.h"
#include "SFML/System/Time.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");

    GameManager gameManager;
    sf::Font textFont;

    if (!textFont.loadFromFile("fonts/JunicodeVF-Roman.ttf"))
    {
        std::cout << "failed to load font" << std::endl;
    }
    else
    {
        std::cout << "loaded font" << std::endl;
    }

    int textSize = 60;
    sf::Color textColor = sf::Color::White;
    TextStyle textStyle(textFont, textColor, textSize);

    TextInputField textInputField(sf::Vector2f(240, 610), textStyle);

    int textHistoryBufferSize = 24;
    int textHistoryVerticalSpacing = 24;
    TextHistory textHistory(textHistoryBufferSize, sf::Vector2f(240, 0), textStyle, textHistoryVerticalSpacing);

    std::basic_string<sf::Uint32> unicode = { 0x16E0, 0x0020, 0x16E1, 0x0020, 0x16E2, 0x0020, 0x16E3, 0x0020, 0x16E4};
    sf::String unicodeString(unicode);
    TextEntity textEntity(unicodeString, sf::Vector2f(10, 10), textStyle);

    std::vector<sf::Drawable*> drawables;
    drawables.push_back(&textHistory);
    drawables.push_back(&textInputField);
    drawables.push_back(&textEntity);

    std::vector<Updateable*> updateables;
    updateables.push_back(&textInputField);

    sf::Clock clock;
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

        sf::Time deltaTime = clock.restart();
        gameManager.updateGame(window, updateables, drawables, deltaTime);
    }

    return 0;
}