#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "GameManager.h"
#include "TextInputField.h"
#include "TextHistory.h"
#include "TextStyle.h"
#include "Updatable.h"
#include "SFML/System/Time.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");

    GameManager gameManager;
    sf::Font textFont;

    if (!textFont.loadFromFile("fonts/Junicode-Regular.ttf"))
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
    int textHistoryVerticalSpacing = 24;
    TextHistory textHistory(textHistoryBufferSize, sf::Vector2f(240, 0), textStyle, textHistoryVerticalSpacing);

    std::vector<sf::Drawable*> drawables;
    drawables.push_back(&textHistory);
    drawables.push_back(&textInputField);

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