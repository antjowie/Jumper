#include "GameStateMain.h"
#include "Game.h"
#include "GameStatePlay.h"
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
			switch (HandleClick(game->window.mapCoordsToPixel(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y))))
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
			game->window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));

			int i = 3;
			const float MULTIPLIER_WIDTH = (float)event.size.width/ (float)background.getLocalBounds().width;
			const float MULTIPLIER_HEIGHT = (float)event.size.height / (float)background.getLocalBounds().height;
			for (std::vector<MenuItem>::iterator button = buttons.begin() ; button != buttons.end(); ++button)
			{
				button->area.top = event.size.height / 6 * i++;
				button->area.height = 60 * MULTIPLIER_HEIGHT;
				button->area.width *= MULTIPLIER_WIDTH;
			}


			background.setScale((float)event.size.width / (float)background.getLocalBounds().width, (float)event.size.height / (float)background.getLocalBounds().height);
			
			break;
		}
	}
}

void GameStateMain::Update(const float dt)
{
	background.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
}

void GameStateMain::Draw()
{
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(0,0,0, 100));

	sf::Text text("N/A", game->texmngr.GetFont("airstream"));
	text.setScale(sf::Vector2f(1.5f, 1.5f));
	text.scale((float)game->window.getSize().x / 1280, (float)game->window.getSize().y / 720);
	
	game->window.draw(background);
	for (auto button : buttons) {
		rectangle.setSize(sf::Vector2f(float(button.area.width), float(button.area.height)));
		rectangle.setPosition(game->window.mapPixelToCoords(sf::Vector2i(button.area.left, button.area.top)));
		text.setPosition(game->window.mapPixelToCoords(sf::Vector2i(button.area.left + 300, button.area.top)));
		text.setString(button.text);
		if(button.area.contains(sf::Mouse::getPosition(game->window))) text.setFillColor(sf::Color::Red);
		else text.setFillColor(sf::Color::Black);
		
		game->window.draw(text);
		game->window.draw(rectangle);
	}
}

GameStateMain::GameStateMain(Game * const game):
	GameState(game)
{
	const sf::Vector2u WINDOW_SIZE= game->window.getSize();
	
	MenuItem play;
	play.action = MenuAction::PLAY;
	play.text = "Play";
	play.area = sf::IntRect(0,WINDOW_SIZE.y / 6*3,WINDOW_SIZE.x,60);
	 
	MenuItem options;
	options.action = MenuAction::OPTIONS;
	options.text = "Options";
	options.area = sf::IntRect(0, WINDOW_SIZE.y / 6 * 4, WINDOW_SIZE.x, 60);

	MenuItem quit;
	quit.action = MenuAction::QUIT;
	quit.text = "Exit";
	quit.area = sf::IntRect(0, WINDOW_SIZE.y / 6 * 5, WINDOW_SIZE.x, 60);

	buttons.reserve(3);
	buttons.push_back(play);
	buttons.push_back(options);
	buttons.push_back(quit);

	background.setTexture(game->texmngr.GetTexture("mainMenuBackground"));
}

void GameStateMain::LoadGame()
{
	game->PushState(new GameStatePlay(game));
}

GameStateMain::MenuAction GameStateMain::HandleClick(const sf::Vector2i coordinates)
{
	for (auto button : buttons) {
		if (button.area.contains(
			// We use this line because pixels are different when window gets resized
			(sf::Vector2i)game->window.mapPixelToCoords(coordinates)))
		{
			if (game->config.debugMode) {
				std::cout << "Mouse x: " << coordinates.x << "\ty: " << coordinates.y << '\n';
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
			}
			return button.action;
		}
	}
	if (game->config.debugMode) std::cout << "Mouse x: " << coordinates.x << "\ty: " << coordinates.y << '\n' << "NOTHING\n";
	return MenuAction::NOTHING;
}
