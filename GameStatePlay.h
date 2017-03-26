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
	sf::Vector2f movement;
	sf::Vector2i scrollMoved;
	
	sf::View view;

	Player player;
	sf::Sprite scrollBackground;
};

