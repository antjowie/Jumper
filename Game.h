#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include <stack>

class Game
{
public:
	sf::RenderWindow window;
	std::stack<GameState*> states;

	void PushState(GameState* const state);
	void PopState();
	void ChangeState(GameState* const state);
	GameState* PeekState() const;

	Game();
	~Game();

private:
	// Makes sure only one instance of this class exists
	static bool initialized;
};

