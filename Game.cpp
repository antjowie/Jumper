#include "Game.h"
#include<cassert>

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

	texmngr.LoadTexture("mainMenuBackground", "media/mainMenuBackground.png");
}

Game::~Game()
{
	while (!states.empty()) PopState();
}

bool Game::initialized = false;