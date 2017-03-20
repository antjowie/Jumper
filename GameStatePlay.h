#pragma once
#include "GameState.h"
#include "Player.h"
#include <SFML\Graphics.hpp>

class GameStatePlay :
	public GameState
{
public:	
	void Input();
	void Update(const float dt);
	void Draw();
	void Resize();

	GameStatePlay(Game* const game);

private:
	int scrollMoved;
	
	sf::View view;

	sf::Vector2f movement;
	Player player;
	sf::Sprite scrollBackground;
};

