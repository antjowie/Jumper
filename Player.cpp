#include "Player.h"

void Player::Move(sf::Vector2f movement, const float dt)
{
	if (movement == sf::Vector2f(0, 0))			anim.ChangeAnimation(0);
	else if (movement == sf::Vector2f(1, 1))	anim.ChangeAnimation(1);
	else if (movement == sf::Vector2f(1, -1))	anim.ChangeAnimation(2);
	else if (movement == sf::Vector2f(-1, 1))	anim.ChangeAnimation(3);
	else if (movement == sf::Vector2f(-1, -1))	anim.ChangeAnimation(4);
	else if (movement == sf::Vector2f(1, 0))	anim.ChangeAnimation(5);
	else if (movement == sf::Vector2f(-1, 0))	anim.ChangeAnimation(6);
	
	anim.Update(dt);

	movement *= dt;
	sprite.move(movement);
}

void Player::Draw(sf::RenderWindow & window)
{
	sprite.setTextureRect(anim.GetFrame());
	window.draw(sprite);
}

Player::Player(const sf::Texture & texture, const std::vector<Animation> anim):
	anim(anim)
{
	sprite.setTexture(texture);
}
