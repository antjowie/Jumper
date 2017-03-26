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

void Game::UpdateConfig(const GameConfig newConfig)
{
	config = newConfig;

	std::ofstream update("config.txt", std::ios::trunc);
	
	// Not sure if this the cleanest solution. It's the best I could come up with.
	update << config.up << '\n'
		<< config.left << '\n'
		<< config.down << '\n'
		<< config.right << '\n'
		<< config.jump << '\n'
		<< config.shoot;

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
	std::ifstream checkConfig("config.txt", std::ios::beg);
	if (checkConfig) {
		std::string configLine;
		std::vector<int> configInts;
		configInts.reserve(6);

		// Loads the file into a vector
		while (std::getline(checkConfig, configLine)) {
			configInts.push_back(std::stoi(configLine));
		}
		// Checks if config file isn't modified externally (by checking the length)
		if (configInts.size() > 7) {
			// TODO: Tell that config file was corrupt
			DefaultConfig();
		}
		// Loads old config file
		else {
			GameConfig tempConfig;
			
			tempConfig.up = (sf::Keyboard::Key)configInts[0];
			tempConfig.left = (sf::Keyboard::Key)configInts[1];
			tempConfig.down = (sf::Keyboard::Key)configInts[2];
			tempConfig.right = (sf::Keyboard::Key)configInts[3];
			
			tempConfig.jump = (sf::Keyboard::Key)configInts[4];
			tempConfig.shoot = (sf::Mouse::Button)configInts[5];

			UpdateConfig(tempConfig);	
		}
	}
	else
	{
		DefaultConfig();
	}
	checkConfig.close();
}

void Game::DefaultConfig()
{
	GameConfig tempConfig;
	tempConfig.up = sf::Keyboard::W;
	tempConfig.left = sf::Keyboard::A;
	tempConfig.down = sf::Keyboard::S;
	tempConfig.right = sf::Keyboard::D;

	tempConfig.jump = sf::Keyboard::Space;
	tempConfig.shoot = sf::Mouse::Button::Left;

	UpdateConfig(tempConfig);
}

bool Game::initialized = false;