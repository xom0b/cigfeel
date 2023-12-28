#include "GameManager.h"

void GameManager::Update(sf::RenderWindow& window, GameState& gameState)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered)
            gameState.ProcessKey(event.text);
    }
}
