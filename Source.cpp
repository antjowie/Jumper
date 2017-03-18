#include "Game.h"
#include "GameStateMain.h"

int main()
{
	Game game;

	game.PushState(new GameStateMain(&game));
	game.Loop();

	return 0;
}