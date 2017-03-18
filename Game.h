#pragma once
#include "GameState.h"
#include "TextureManager.h"
#include <SFML\Graphics.hpp>
#include <stack>

class Game
{
public:
	sf::RenderWindow window;
	std::stack<GameState*> states;

	TextureManager texmngr;

	void PushState(GameState* const state);
	void PopState();
	void SwitchState(GameState* const state);
	GameState* PeekState() const;

	void Loop();

	Game();
	~Game();

private:
	// Makes sure only one instance of this class exists
	static bool initialized;
};

