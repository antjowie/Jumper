#pragma once
#include "AnimationHandler.h"
#include <SFML\Graphics.hpp>
#include <vector>

class Player
{
public:
	void Input(const sf::Vector2f movement);
	void Update(const float dt);
	void Draw(sf::RenderWindow& window);

	Player(const sf::Texture& texture, const std::vector<Animation> animations);

private:
	AnimationHandler anim;
	sf::Sprite sprite;
};

