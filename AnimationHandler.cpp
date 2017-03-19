#include "AnimationHandler.h"
#include <math.h>

Animation::Animation(const sf::IntRect frameSize, const float animDuration, const int animLength, const bool isLooping):
	frameSize(frameSize),
	animDuration(animDuration),
	animLength(animLength),
	isLooping(isLooping)
{
}

void AnimationHandler::Update(const float dt)
{
	elapsedTime += dt;
	// Cancel update if animation is invalid
	if (animType == -1 || animType > (int)anim.size()) return;
	
	animNum += int(elapsedTime) / int(anim[animType].animDuration);
	// Makes sure we stay in bounds of the animation
	if (animNum > anim[animType].animLength) {
		if (!anim[animType].isLooping) {
			elapsedTime = fmod(elapsedTime, anim[animType].animDuration);
			currentFrame = firstFrame;
		}
		else {
			elapsedTime -= dt;
			--animNum;
		}
	}
	// Updates frame
	currentFrame.left = animNum*anim[animType].frameSize.width;
	frame.setTextureRect(currentFrame);
}

void AnimationHandler::Draw(sf::RenderWindow & window)
{
	if (animType != -1)	window.draw(frame);
}

void AnimationHandler::ChangeAnimation(const int animType)
{
	if (animType == -1 || this->animType == animType || animType > (int)anim.size()) return;
	
	elapsedTime = fmod(elapsedTime, anim[animType].animDuration);
	firstFrame = currentFrame = anim[animType].frameSize;
	this->animType = animType;
}

AnimationHandler::AnimationHandler(const std::vector<Animation>& animations, const sf::Texture & texture):
	anim(animations),
	elapsedTime(0)
{
	frame.setTexture(texture);
}