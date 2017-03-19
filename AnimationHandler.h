#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

struct Animation
{
	sf::IntRect frameSize;
	float animDuration;
	int animLength;
	bool isLooping;

	Animation(const sf::IntRect frameSize, const float animDuration, const int animLength, const bool isLooping = true);
};

class AnimationHandler
{
public:
	void Update(const float dt);
	void Draw(sf::RenderWindow& window);
	void ChangeAnimation(const int animType = -1);

	AnimationHandler(const std::vector<Animation>& animations, const sf::Texture& texture);

private:
	sf::IntRect firstFrame;
	sf::IntRect currentFrame;
	std::vector<Animation> anim;
	// Vetical
	int animType;
	// Horizontal
	int animNum;

	sf::Sprite frame;
	float elapsedTime;
};