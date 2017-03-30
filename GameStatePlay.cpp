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
			if (event.mouseButton.button == game->config[5]); //TODO: Make shoot function
			break;

		case sf::Event::Resized:
			Resize();
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)game->config[0])) movement -= sf::Vector2f(0, 2.f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)game->config[1])) movement -= sf::Vector2f(2.f, 0);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)game->config[2]))movement += sf::Vector2f(0, 2.f);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)game->config[3])) movement += sf::Vector2f(2.f, 0);
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)game->config[4])) movement += sf::Vector2f(0, -2.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) game->PopThisState = true;

	movement*= 0.8f;
	if (movement.x < 0.1f && movement.x > -0.1f) movement.x = 0;
	if (movement.y < 0.1f && movement.y > -0.1f) movement.y = 0;

	scrollMoved.x += int(movement.x * 0.2f);
	scrollMoved.y += int(movement.y * 0.2f);
	if(scrollMoved.y > 0) scrollMoved.y = 0;
	else if (scrollMoved.y < -360) scrollMoved.y = -360;
}

void GameStatePlay::Update(const float dt)
{
	scrollBackground.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), view));
	scrollBackground.setTextureRect(sf::IntRect(scrollMoved.x, 360 + scrollMoved.y, game->window.getSize().x, 360));

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
	scrollBackground.setScale((float)game->window.getSize().x / 640, game->window.getSize().y / (scrollBackground.getLocalBounds().height / 2.f));
	// 1280 is the fixed size of the scrollBackground to show
}

GameStatePlay::GameStatePlay(Game* const game) :
	GameState(game),
	player(game->texmngr.GetTexture("playerSpritesheet"),
	{
		Animation(0,3,0.5f),		// Static
		Animation(0,3,0.1f,false),	// Jump right
		Animation(0,3,0.1f,false),	// Fall right
		Animation(0,3,0.1f,false),	// Jump left
		Animation(0,3,0.1f,false),	// Fall left
		Animation(0,3,0.15f),		// Run right
		Animation(0,3,0.15f)		// Run left
	}),
	movement(0,0),
	scrollMoved(0,0)
{
	scrollBackground.setTexture(game->texmngr.GetTexture("scrollBackground1.6"));
	Resize();
}