#include "Player.h"

void Player::Input(const sf::Vector2f movement)
{
	if (movement.x == 0 && movement.y == 0) anim.ChangeAnimation(0);			// Static
	else if (movement.x < -0.1f && movement.y < -0.1f) anim.ChangeAnimation(3);	// Jump left
	else if (movement.x < -0.1f && movement.y > 0.1f) anim.ChangeAnimation(4);	// Drop left
	else if (movement.x > 0.1f && movement.y < -0.1f) anim.ChangeAnimation(1);	// Jump right
	else if (movement.x > 0.1f && movement.y > 0.1f) anim.ChangeAnimation(2);	// Drop right
	else if (movement.x == 0 && movement.y < -0.1f) anim.ChangeAnimation(1);	// Jump static
	else if (movement.x == 0 && movement.y > 0.1f) anim.ChangeAnimation(2);		// Drop static
	else if (movement.x > 0.1f && movement.y == 0) anim.ChangeAnimation(5);		// Walk right
	else if (movement.x < -0.1f && movement.y == 0) anim.ChangeAnimation(6);	// Walk left

	sprite.move(movement);
}

void Player::Update(const float dt)
{
	anim.Update(dt);
}

void Player::Draw(sf::RenderWindow & window)
{
	sprite.setTextureRect(anim.GetFrame());
	window.draw(sprite);
}

Player::Player(const sf::Texture& texture, const std::vector<Animation> animations):
	anim(sf::IntRect(0,0,32,32))
{
	sprite.setTexture(texture);
	for (auto animation : animations) {
		anim.AddAnimation(animation);
	}
	sprite.setScale(3, 3);
}
