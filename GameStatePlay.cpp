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
			Resize();
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(game->config.up)) movement -= sf::Vector2f(0, 2.f);
	if (sf::Keyboard::isKeyPressed(game->config.left)) movement -= sf::Vector2f(2.f, 0);
	if (sf::Keyboard::isKeyPressed(game->config.down))	movement += sf::Vector2f(0, 2.f);
	if (sf::Keyboard::isKeyPressed(game->config.right)) movement += sf::Vector2f(2.f, 0);
	if (sf::Keyboard::isKeyPressed(game->config.jump)) movement += sf::Vector2f(0, -2.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) game->PopThisState = true;

	movement*= 0.8f;
	scrollMoved += (int)movement.x;
	if (game->config.debugMode) std::cout << "Movement x: " << movement.x << "\ty: " << movement.y << '\n';
	
}

void GameStatePlay::Update(const float dt)
{

	scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
	scrollBackground.setTextureRect(sf::IntRect(scrollMoved, 0 , game->window.getSize().x, 720));

	view.move(movement.x, 0);
	if (game->config.debugMode) std::cout << "scrollMoved = " << scrollMoved << '\n';
} 

void GameStatePlay::Draw()
{
	game->window.draw(scrollBackground);
	player.Draw(game->window);

	game->window.setView(view);
}

void GameStatePlay::Resize()
{
	view.setSize((sf::Vector2f)game->window.getSize());
	view.setCenter((sf::Vector2f)game->window.getSize() * 0.5f);
	scrollBackground.setScale(game->window.getSize().x / (scrollBackground.getLocalBounds().width / 2), game->window.getSize().y / scrollBackground.getLocalBounds().height);
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
	scrollBackground.setTexture(game->texmngr.GetTexture("scrollBackground1.5"));
	Resize();
}
