#pragma once
#include "GameState.h"
#include "TextureManager.h"
#include <SFML\Graphics.hpp>
#include <stack>
#include <vector>

class Game
{
public:
	sf::RenderWindow window;

	//0 is up, 1 is left, 2 is down, 3 is right, 4 is jump, 5 is shoot
	std::vector<int> config;
	TextureManager texmngr;

	bool PopThisState;
	
	void PushState(GameState* const state);
	void PopState();
	void SwitchState(GameState* const state);
	GameState* PeekState() const;

	void UpdateConfig(const std::vector<int> newConfig);

	void Loop();

	Game();
	~Game();

private:
	std::stack<GameState*> states;
	
	void BootConfig();
	void DefaultConfig();

	// Makes sure only one instance of this class exists
	static bool initialized;
};

