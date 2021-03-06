#pragma once

class Game;

class GameState
{
public:
	virtual void Input() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Draw() = 0;
	// Resize exists if user resizes window and pops state
	virtual void Resize() = 0;

	GameState(Game* const game);
protected:
	Game* const game;
};