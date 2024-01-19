#include "TextInputController.h"

TextInputController::TextInputController()
{
    textFont = new sf::Font;

    if (!textFont->loadFromFile("fonts/JunicodeVF-Roman.ttf"))
    {
        std::cout << "failed to load font" << std::endl;
    }
    else
    {
        std::cout << "loaded font" << std::endl;
    }

    int textSize = TEXT_SIZE;
    sf::Color textColor = sf::Color::White;
    TextStyle textStyle(textFont, textColor, textSize);

    textInputField = new TextInputField(
        sf::IntRect(TEXT_INPUT_X, TEXT_INPUT_Y, TEXT_INPUT_PADDING_X, TEXT_INPUT_PADDING_Y),
        sf::Vector2i(TEXT_INPUT_PADDING_X, TEXT_INPUT_PADDING_Y),
        textStyle);

    textHistory = new TextHistory(
        sf::FloatRect(TEXT_HISTORY_X, TEXT_HISTORY_Y, TEXT_HISTORY_WIDTH, TEXT_HISTORY_HEIGHT),
        sf::Vector2f(TEXT_HISTORY_PADDING_X, TEXT_HISTORY_PADDING_Y),
        textStyle, 
        TEXT_HISTORY_SPACING_Y);

    debug_loadFormattingTest();
}

TextInputController::~TextInputController()
{
    delete textFont;
    delete textInputField;
    delete textHistory;
}

void TextInputController::processEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed && event.key.scancode == sf::Keyboard::Scan::Enter)
    {
        std::string input = textInputField->getInput();
        if (input.length() > 0)
        {
            textHistory->add(textInputField->getInput());
            textInputField->clearInput();
        }
    }
    else
    {
        textInputField->processEvent(event);
    }
}

void TextInputController::update(sf::Time deltaTime)
{
    textInputField->update(deltaTime);
}

void TextInputController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    textHistory->draw(target, states);
    textInputField->draw(target, states);
}

void TextInputController::debug_loadFormattingTest()
{
    std::ifstream debugFile("data/debug_textformat.txt");
    if (!debugFile.is_open())
    {
        std::cout << "formatting test file is open, cannot read" << std::endl;
        return;
    }

    std::string fileContent((std::istreambuf_iterator<char>(debugFile)), std::istreambuf_iterator<char>());
    debugFile.close();

    textHistory->add(fileContent);
}
