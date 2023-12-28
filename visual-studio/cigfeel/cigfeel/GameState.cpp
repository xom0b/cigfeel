#include "GameState.h"

GameState::GameState(size_t bufferSize) : m_bufferSize(bufferSize), m_lastIndex(0)
{
	m_inputBuffer = new sf::String[bufferSize];
}

GameState::~GameState()
{
	delete m_inputBuffer;
}

void GameState::Submit(sf::String s)
{
	m_lastIndex = (m_lastIndex + 1) % (m_bufferSize - 1);
	m_inputBuffer[m_lastIndex] = s;
}

void GameState::Set(sf::String s)
{
	m_inputBuffer[m_lastIndex] = s;
}

void GameState::ProcessKey(sf::Event::TextEvent& keyEvent)
{

}

size_t GameState::GetSize()
{
	return m_bufferSize;
}

size_t GameState::GetLastIndex()
{
	return m_lastIndex;
}
