#include "GameStatePlay.h"
#include "Game.h"

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
	if (movement.x < 0.1f && movement.x > -0.1f) movement.x = 0;
	if (movement.y < 0.1f && movement.y > -0.1f) movement.y = 0;

	scrollMoved += (int)movement.x;
}

void GameStatePlay::Update(const float dt)
{
	scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
	scrollBackground.setTextureRect(sf::IntRect(scrollMoved, 0 , game->window.getSize().x, 720));

	player.Input(movement);
	player.Update(dt);

	view.move(movement.x, 0);
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
	scrollBackground.setScale(game->window.getSize().x / 1280, game->window.getSize().y / scrollBackground.getLocalBounds().height);
	// 1280 is the fixed size of the scrollBackground to show
}

GameStatePlay::GameStatePlay(Game* const game) :
	GameState(game),
	player(game->texmngr.GetTexture("playerSpritesheet"),
	{
		Animation(0,3,0.2f),		// Static
		Animation(0,3,0.2f,false),	// Jump right
		Animation(0,3,0.2f,false),	// Fall right
		Animation(0,3,0.2f,false),	// Jump left
		Animation(0,3,0.2f,false),	// Fall left
		Animation(0,3,0.2f),		// Run right
		Animation(0,3,0.2f)			// Run left
	}),
	movement(0,0),
	scrollMoved(0)
{
	scrollBackground.setTexture(game->texmngr.GetTexture("scrollBackground1.5"));
	Resize();
}
