#pragma once
#include "AnimationHandler.h"
#include <SFML\Graphics.hpp>

class Player
{
public:
	sf::Sprite sprite;
	
	void Move(sf::Vector2f movement, const float dt);
	void Shoot(const sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);

	Player(const sf::Texture& texture, const std::vector<Animation> anim);
private:
	AnimationHandler anim;
};

