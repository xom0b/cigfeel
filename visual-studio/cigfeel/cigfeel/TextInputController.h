#pragma once
#include <iostream>

#include "Controller.h"
#include "TextStyle.h"
#include "TextInputField.h"
#include "TextHistory.h"
#include "LayoutMacros.h"

class TextInputController : public Controller, public Updateable, public sf::Drawable
{
	sf::Font* textFont;
	TextInputField* textInputField;
	TextHistory* textHistory;
public:
	TextInputController();
	~TextInputController();
	void processEvent(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

