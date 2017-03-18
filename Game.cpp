#include "Game.h"
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>

void Game::PushState(GameState* const state)
{
	states.push(state);
}

void Game::PopState()
{
	if (!states.empty()) {
		delete states.top();
		states.pop();
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
	
	update << config.up << '\n'
		<< config.left << '\n'
		<< config.down << '\n'
		<< config.right << '\n'
		<< config.jump << '\n'
		<< config.shoot << '\n'
		<< config.debugMode;

	update.close();
}

void Game::Loop()
{
	sf::Clock clock;
	float dt;

	while (window.isOpen()) {
		dt = clock.getElapsedTime().asSeconds();

		if (PeekState() == nullptr) continue;

		PeekState()->Input();
		PeekState()->Update(dt);
		window.clear(sf::Color::Black);
		PeekState()->Draw();
		window.display();
	}
}

Game::Game()
{
	// Makes sure only one instance of the class is created
	assert(!initialized);
	initialized = true;

	window.create(sf::VideoMode(1280, 720), "Don't read the title, play the game");
	window.setFramerateLimit(60);

	BootConfig();
	texmngr.LoadTexture("mainMenuBackground", "media/mainMenuBackground.png");
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
		configInts.reserve(7);

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
			std::cout << "good size";
			GameConfig tempConfig;
			
			tempConfig.up = (sf::Keyboard::Key)configInts[0];
			tempConfig.left = (sf::Keyboard::Key)configInts[1];
			tempConfig.down = (sf::Keyboard::Key)configInts[2];
			tempConfig.right = (sf::Keyboard::Key)configInts[3];
			
			tempConfig.jump = (sf::Keyboard::Key)configInts[4];
			tempConfig.shoot = (sf::Mouse::Button)configInts[5];
			tempConfig.debugMode = (configInts[6] == 0 ? false : true);

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
	tempConfig.down = sf::Keyboard::D;
	tempConfig.right = sf::Keyboard::R;

	tempConfig.jump = sf::Keyboard::Space;
	tempConfig.shoot = sf::Mouse::Button::Left;

	tempConfig.debugMode = false;

	UpdateConfig(tempConfig);
}

bool Game::initialized = false;