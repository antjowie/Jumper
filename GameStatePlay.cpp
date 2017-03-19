#include "GameStatePlay.h"
#include "Game.h"
#include <iostream>
#include <math.h>

void GameStatePlay::Input()
{
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game->window.close();
		}
	}
}

void GameStatePlay::Update(const float dt)
{
	std::cout << scrollBackground.getLocalBounds().width << '\n';
	if (scrollMoved > 1280 * 2) {
		scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
		scrollMoved = fmod(scrollMoved,1280.f * 2.f);
	}
	else if (scrollMoved < 0) {

	}

	view.move(9.1f, 0);
	scrollMoved += 9.1f;
} 

void GameStatePlay::Draw()
{
	game->window.draw(scrollBackground);
	game->window.setView(view);
}

GameStatePlay::GameStatePlay(Game* const game):
	GameState(game),
	scrollMoved(0)
{
	sf::Vector2f WINDOW_SIZE = (sf::Vector2f)game->window.getSize();
	view.setSize(WINDOW_SIZE);
	WINDOW_SIZE * 0.5f;
	view.setCenter(WINDOW_SIZE);

	scrollBackground.setTexture(game->texmngr.GetTexture("scrollBackground1.1"));
	scrollBackground.setTextureRect(sf::IntRect(0, 0, 1280*3, 720));
	scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
}