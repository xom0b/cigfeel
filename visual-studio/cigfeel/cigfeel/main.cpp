#include <SFML/Graphics.hpp>
#include "GameDrawer.h"
#include "GameManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "cigfeel");
    GameManager gameManager;
    GameState gameState(480);
    GameDrawer gameDrawer;

    while (window.isOpen())
    {
        
        gameDrawer.DrawGame(window, gameState);
    }

    return 0;
}