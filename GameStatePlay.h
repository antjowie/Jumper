#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>

class GameStatePlay :
	public GameState
{
public:	

	void Input();
	void Update(const float dt);
	void Draw();

	GameStatePlay(Game* const game);

private:
	float scrollMoved;
	
	sf::View view;

	sf::Sprite scrollBackground;
};

