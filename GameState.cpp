#include "GameState.h"
#include <cassert>

GameState::GameState(Game * const game):
	game(game)
{
	// Makes sure that only one instance exists
	assert(!initialized);
	initialized = true;
}

bool GameState::initialized = false;