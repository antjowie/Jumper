#include "Game.h"
#include <cassert>
#include <fstream>
#include <string>

void Game::PushState(GameState* const state)
{
	states.push(state);
}

void Game::PopState()
{
	if (!states.empty()) {
		delete states.top();
		states.pop();
		// Although we should use peekstate, this spares us one operation (probably doesn't make an impact though)
		if (!states.empty()) states.top()->Resize();
	}
}

void Game::SwitchState(GameState* const state)
{
	PopState();
	PushState(state);
}

GameState * Game::PeekState() const
{
	if (states.empty()) return nullptr;
	return states.top();
}

void Game::UpdateConfig(const std::vector<int> newConfig)
{
	config = newConfig;

	std::ofstream update("config.txt", std::ios::trunc, std::ios::binary);
	
	for (auto aConfig : newConfig)
		update << aConfig << ' ';
	 
	update.close();
}

void Game::Loop()
{
	sf::Clock clock;
	float dt;

	while (window.isOpen()) {
		dt = clock.restart().asSeconds();
		if (PeekState() == nullptr) continue;

		PeekState()->Input();
		PeekState()->Update(dt);
		window.clear(sf::Color::Black);
		PeekState()->Draw();
		window.display();
	
		if (PopThisState) {
			PopThisState = false;
			PopState();
		}
	}
}

Game::Game():
	PopThisState(false)
{
	// Makes sure only one instance of the class is created
	assert(!initialized);
	initialized = true;

	window.create(sf::VideoMode(1280, 720), "Don't read the title, play the game");
	window.setFramerateLimit(60);

	BootConfig();
	texmngr.LoadTexture("playerSpritesheet", "media/playerSpritesheet.png");
	texmngr.LoadTexture("mainMenuBackground", "media/mainMenuBackground.png");
	texmngr.LoadTexture("scrollBackground1.6", "media/scrollBackground1.6.png");
	texmngr.GetTexture("scrollBackground1.6").setRepeated(true);
	texmngr.GetTexture("scrollBackground1.6").setSmooth(true);
	texmngr.LoadFont("airstream", "media/airstream.ttf");
}

Game::~Game()
{
	while (!states.empty()) PopState();
}

void Game::BootConfig()
{
	std::ifstream checkConfig("config.txt", std::ios::beg, std::ios::binary);

	if (checkConfig) {
		int val;
		while (checkConfig) {
			checkConfig >> val;
			if (val > sf::Keyboard::Z) {
				// TODO: Tell config file is modified externally and may be corrupt
			}
			config.push_back(val);
		}
		config.pop_back();
			checkConfig.close();
		if (config.size() != 6) {
			// TODO: Tell config file was corrupt 
			DefaultConfig();
		}
	}
	else {
		DefaultConfig();
	}
}

void Game::DefaultConfig()
{
	std::vector<int> tempConfig;
	tempConfig.push_back(sf::Keyboard::W);
	tempConfig.push_back(sf::Keyboard::A);
	tempConfig.push_back(sf::Keyboard::S);
	tempConfig.push_back(sf::Keyboard::D);

	tempConfig.push_back(sf::Keyboard::Space);
	tempConfig.push_back(sf::Mouse::Button::Left);

	UpdateConfig(tempConfig);
}

bool Game::initialized = false;