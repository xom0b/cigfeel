#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "cigfeel");
    sf::CircleShape shape(50.f);
    sf::String stringText("cigfeel");
    sf::Font stringFont;
    sf::Text text(stringText, stringFont, 30U);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }

    return 0;
}