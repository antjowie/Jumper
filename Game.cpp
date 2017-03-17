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

void Game::ChangeState(GameState* const state)
{
	PopState();
	PushState(state);
}

GameState * Game::PeekState() const
{
	if (states.empty()) return nullptr;
	return states.top();
}

Game::Game()
{
	assert(!initialized);
	initialized = true;
}


Game::~Game()
{
	while (!states.empty()) PopState;
}

bool Game::initialized = false;