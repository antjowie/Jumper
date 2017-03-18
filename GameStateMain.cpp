#include "GameStateMain.h"
#include "Game.h"
#include <iostream>

void GameStateMain::Input()
{
	sf::Event event;
	while (game->window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) game->window.close();
			break;

		case sf::Event::MouseButtonPressed:
			switch (HandleClick(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
			{
			case MenuAction::PLAY:
				LoadGame();
				break;
			case MenuAction::OPTIONS:
				// TODO: make options screen
				break;
			case MenuAction::QUIT:
				game->window.close();
				break;
			}
			break;

		case sf::Event::Resized:
			break;
		}
	}
}

void GameStateMain::Update(const float dt)
{
}

void GameStateMain::Draw()
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(0,0,0, 100));

	//sf::Text text("N/A", game->texmngr.GetFont("airstream"));
	//text.setFillColor(sf::Color::Black);


	game->window.draw(background);
	for (auto button : buttons) {
		rectangle.setSize(sf::Vector2f(float(button.area.width), float(button.area.height)));
		rectangle.setPosition(sf::Vector2f(float(button.area.left), float(button.area.top)));
		
		game->window.draw(rectangle);
	}
}

GameStateMain::GameStateMain(Game * const game):
	GameState(game)
{
	const sf::Vector2u WINDOW_SIZE= game->window.getSize();
	
	MenuItem play;
	play.action = MenuAction::PLAY;
	play.text = "Start game";
	play.area = sf::IntRect(0,330,WINDOW_SIZE.x,60);
	 
	MenuItem options;
	options.action = MenuAction::OPTIONS;
	options.text = "Options";
	options.area = sf::IntRect(0, 410, WINDOW_SIZE.x, 60);

	MenuItem quit;
	quit.action = MenuAction::QUIT;
	quit.text = "Quit game";
	quit.area = sf::IntRect(0, 490, WINDOW_SIZE.x, 60);

	buttons.reserve(3);
	buttons.push_back(play);
	buttons.push_back(options);
	buttons.push_back(quit);

	background.setTexture(game->texmngr.GetTexture("mainMenuBackground"));
}

void GameStateMain::LoadGame()
{
}

GameStateMain::MenuAction GameStateMain::HandleClick(const sf::Vector2i coordinates)
{
	for (auto button : buttons) {
		if (button.area.contains(coordinates))
		{
			if(game->config.debugMode)
				switch (button.action)
				{
				case MenuAction::PLAY:
					std::cout << "PLAY\n";
					break;
				case MenuAction::OPTIONS:
					std::cout << "OPTIONS\n";
					break;
				case MenuAction::QUIT:
					std::cout << "QUIT\n";
					break;
				case MenuAction::NOTHING:
					std::cout << "NOTHING\n";
					break;
				default:
					std::cout << "DEFAULT\n";
					break;
				}
			return button.action;
		}
	}
	if (game->config.debugMode) std::cout << "NOTHING\n";
	return MenuAction::NOTHING;
	
}
