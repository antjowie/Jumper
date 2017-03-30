#include "AnimationHandler.h"
#include <math.h>

Animation::Animation(const unsigned int startFrame, const unsigned int endFrame, const float duration, const bool isRepeated):
	startFrame(startFrame),
	endFrame(endFrame),
	duration(duration),
	isRepeated(isRepeated)
{
}

int Animation::GetLength() const
{
	return endFrame - startFrame + 1;
}

void AnimationHandler::AddAnimation(const Animation anim)
{
	animations.push_back(anim);
}

void AnimationHandler::ChangeAnimation(unsigned int animID)
{
	if (animID == currentAnim || animID > animations.size()) return;
	elapsed = 0.0f;
	currentAnim = animID;
	
	sf::IntRect rect;
	rect = frameSize;
	rect.top = rect.height * animID;
	currentFrame = rect;
}

void AnimationHandler::Update(const float dt)
{
	if (currentAnim >= animations.size() || currentAnim < 0) return; 

	const float duration = animations[currentAnim].duration;
	if (int((elapsed + dt) / duration) > int((elapsed / duration))) {
		int frame = int((elapsed + dt) / duration);
		if (!animations[currentAnim].isRepeated && frame > animations.at(currentAnim).endFrame) 
			frame = animations[currentAnim].endFrame;
		else frame %= animations[currentAnim].GetLength();

		sf::IntRect rect = frameSize;
		rect.left = rect.width * frame;
		rect.top = rect.height * currentAnim;
		currentFrame = rect;
	}
	
	elapsed += dt;
	if (elapsed > duration * animations[currentAnim].GetLength())
		fmod(elapsed, duration);
}

sf::IntRect AnimationHandler::GetFrame() const
{
	return currentFrame;
}

AnimationHandler::AnimationHandler():
	elapsed(0), 
	currentAnim(-1)
{
}

AnimationHandler::AnimationHandler(const sf::IntRect frameSize):
	elapsed(0),
	currentAnim(-1),
	frameSize(frameSize)
{
}
