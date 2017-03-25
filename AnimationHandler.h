#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

struct Animation
{
	unsigned int startFrame;
	unsigned int endFrame;

	float duration;
	bool isRepeated;

	Animation(const unsigned int startFrame, const unsigned int endFrame, const float duration, const bool isRepeated = true);
	int GetLength() const;
};

class AnimationHandler
{
public:
	void AddAnimation(const Animation anim);
	void ChangeAnimation(unsigned int animID);
	void Update(const float dt);
	sf::IntRect GetFrame() const;

	AnimationHandler();
	AnimationHandler(const sf::IntRect frameSize);

private:
	sf::IntRect frameSize;
	sf::IntRect currentFrame;

	std::vector<Animation> animations;

	int currentAnim;
	float elapsed;
};