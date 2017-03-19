#include "GameStatePlay.h"
#include "Game.h"
#include <iostream>

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
	if (game->config.debugMode) std::cout << "scrollMoved = " << scrollMoved << '\n';
	if (scrollMoved > 1280 * 2) {
		if(game->config.debugMode) std::cout << "Shifting scrollBackground from right to left\n";
		scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
		scrollMoved -= 1280.f * 2.f;
	}
	else if (scrollMoved < 0) {
		if (game->config.debugMode) std::cout << "Shifting scrollBackground from left to right\n";
		scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(-1280*2, 0), view));
		scrollMoved += 1280.f * 2.f;
	}

	sf::Vector2f moved(1, 0);
	view.move(moved);
	scrollMoved += moved.x;
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