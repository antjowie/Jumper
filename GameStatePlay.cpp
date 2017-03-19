#include "GameStatePlay.h"
#include "Game.h"
#include <iostream>

void GameStatePlay::Input()
{
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			game->PopThisState = true;
			// TODO: make pause screen
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == game->config.shoot); //TODO: Make shoot function
			break;

		case sf::Event::Resized:
			scrollMoved = 0;
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(game->config.up)) movement -= sf::Vector2f(0, 2.f);
	else if (sf::Keyboard::isKeyPressed(game->config.left)) movement -= sf::Vector2f(2.f, 0);
	else if (sf::Keyboard::isKeyPressed(game->config.down))	movement += sf::Vector2f(0, 2.f);
	else if (sf::Keyboard::isKeyPressed(game->config.right)) movement += sf::Vector2f(2.f, 0);
	else if (sf::Keyboard::isKeyPressed(game->config.jump)) movement += sf::Vector2f(0, -2.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) game->PopThisState = true;

	movement*= 0.8f;
	if (game->config.debugMode) std::cout << "Movement x: " << movement.x << "\ty: " << movement.y << '\n';
	

}

void GameStatePlay::Update(const float dt)
{
	const int WINDOW_WIDHT = (int)game->window.getSize().x;
	std::cout << WINDOW_WIDHT << '\n';
	if (game->config.debugMode) std::cout << "scrollMoved = " << scrollMoved << '\n';
	if (scrollMoved > WINDOW_WIDHT * 2) {
		if(game->config.debugMode) std::cout << "Shifting scrollBackground from right to left\n";
		scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
		scrollMoved -= WINDOW_WIDHT * 2.f;
	}
	else if (scrollMoved < 0) {
		if (game->config.debugMode) std::cout << "Shifting scrollBackground from left to right\n";
		scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(WINDOW_WIDHT*2, 0), view));
		scrollMoved += WINDOW_WIDHT * 2.f;
	}


	view.move(movement.x,0);
	scrollMoved += movement.x;
} 

void GameStatePlay::Draw()
{
	game->window.draw(scrollBackground);
	player.Draw(game->window);

	game->window.setView(view);
}

GameStatePlay::GameStatePlay(Game* const game) :
	GameState(game),
	player(game->texmngr.GetTexture("playerSpritesheet"),
	{
		Animation(sf::IntRect(0,0,32,32),2.0f,4,true),			// Static
		Animation(sf::IntRect(0,32,32,32),2.0f,4,true),			// Jump right
		Animation(sf::IntRect(0,32 * 2,32,32),2.0f,4,false),	// Fall right
		Animation(sf::IntRect(0,32 * 3,32,32),2.0f,4,true),		// Jump left
		Animation(sf::IntRect(0,32 * 4,32,32),2.0f,4,false),	// Fall left
		Animation(sf::IntRect(0,32 * 5,32,32),2.0f,4,true),		// Run right
		Animation(sf::IntRect(0,32 * 6,32,32),2.0f,4,true)		// Run left
	}),
	movement(0,0),
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
