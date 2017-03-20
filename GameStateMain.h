#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameStateMain :
	public GameState
{
public:
	virtual void Input();
	virtual void Update(const float dt);
	virtual void Draw();
	virtual void Resize();

	GameStateMain(Game* const game);

private:
	enum class MenuAction { PLAY, OPTIONS, QUIT, NOTHING };
	
	struct MenuItem {
		std::string text;
		sf::IntRect area;
		MenuAction action;
	};

	std::vector<MenuItem> buttons;
	sf::Sprite background;

	void LoadGame();
	MenuAction HandleClick(const sf::Vector2i coordinates);
};

