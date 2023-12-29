#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "GameDrawer.h"
#include "TextInputField.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");

    GameDrawer gameDrawer;
    sf::Font font;
    int fontSize = 24;

    if (!font.loadFromFile("fonts\\Junicode-Regular.ttf"))
    {
        std::cout << "failed to load font" << std::endl;
    }
    else
    {
        std::cout << "loaded font" << std::endl;
    }

    TextInputField textInputField(sf::Vector2f(240, 0), font, sf::Color::White, fontSize);
    TextHistory textHistory(30, sf::Vector2f(240, 0), font);

    std::vector<sf::Drawable*> drawables;
    drawables.push_back(&textHistory);

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