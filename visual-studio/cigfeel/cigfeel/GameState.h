#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
class GameState
{
	size_t m_lastIndex;
	size_t m_bufferSize;
	sf::String  * m_inputBuffer;

public:
	GameState(size_t bufferSize);
	~GameState();
	void Submit(sf::String s);
	void Set(sf::String s);
	size_t GetSize();
	size_t GetLastIndex();
	void ProcessKey(sf::Event::TextEvent& keyEvent);
};

