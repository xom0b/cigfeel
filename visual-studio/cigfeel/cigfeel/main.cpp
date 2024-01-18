#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include "SFML/System/Time.hpp"

#include "GameManager.h"
#include "TextInputController.h";
#include "LayoutMacros.h"
#include "DebugDrawer.h"


//std::basic_string<sf::Uint32> unicode = { 0x16E0, 0x0020, 0x16E1, 0x0020, 0x16E2, 0x0020, 0x16E3, 0x0020, 0x16E4};
//sf::String unicodeString(unicode);
//TextEntity textEntity(unicodeString, sf::Vector2f(10, 10), textStyle);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "cigfeel");

    GameManager gameManager;

    TextInputController textInputController;

    std::vector<Controller*> controllers;
    controllers.push_back(&textInputController);

    std::vector<sf::Drawable*> drawables;
    drawables.push_back(&textInputController);

    std::vector<Updateable*> updateables;
    updateables.push_back(&textInputController);

    sf::Clock clock;
    
    DebugDrawer debugDrawer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gameManager.input(controllers, event);
        }

        sf::Time deltaTime = clock.restart();
        gameManager.update(updateables, deltaTime);

        window.clear();
        debugDrawer.draw(window);
        gameManager.draw(drawables, window);
        window.display();
    }

    return 0;
}