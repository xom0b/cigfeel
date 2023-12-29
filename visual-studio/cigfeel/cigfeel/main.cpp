#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "GameDrawer.h"

#include <filesystem>
#include <iostream>

int main()
{
    std::cout << "my directory is :" << std::filesystem::current_path() << "\n";

    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");

    GameDrawer gameDrawer;
    TextHistory textHistory(30);

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
                textHistory.submit();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                textHistory.append(sf::String(event.text.unicode));
            }
        }

        gameDrawer.drawGame(window, drawables);
    }

    return 0;
}