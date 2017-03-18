#pragma once
#include "GameState.h"
#include "TextureManager.h"
#include <SFML\Graphics.hpp>
#include <stack>

class Game
{
public:
	struct GameConfig {
		sf::Keyboard::Key up, left, down, right, jump;
		sf::Mouse::Button shoot;
		bool debugMode;
	};

	sf::RenderWindow window;
	std::stack<GameState*> states;

	TextureManager texmngr;
	GameConfig config;

	void PushState(GameState* const state);
	void PopState();
	void SwitchState(GameState* const state);
	GameState* PeekState() const;

	void UpdateConfig(const GameConfig newConfig);

	void Loop();

	Game();
	~Game();

private:
	void BootConfig();
	void DefaultConfig();

	// Makes sure only one instance of this class exists
	static bool initialized;
};

