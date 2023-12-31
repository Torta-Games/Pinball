#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Application.h"
#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 30

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	bool loop = true;
	// Allows the animation to keep going back and forth
	bool pingpong = false;
	bool flip = false;
	int loopCount = 0;

	float currentFrame = 0.0f;
	int totalFrames = 0;
	int pingpongCount = 0;
	int pingpongDirection = 1;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Reset()
	{
		currentFrame = 0;
	}

	void ResetLoopCount()
	{
		loopCount = 0;
	}


	bool HasFinished()
	{
		return !loop && !pingpong && loopCount > 0;
	}

	void Update()
	{
		currentFrame += speed;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop) ? 0.0f : totalFrames - 1;
			++loopCount;
		}
	}

	int GetLoopCount() const
	{
		return loopCount;
	}

	int GetPingPongCount() const
	{
		return pingpongCount;
	}

	float GetCurrentFrameCount() const
	{
		return currentFrame;
	}

	const SDL_Rect& GetCurrentFrame() const
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
			actualFrame = totalFrames - currentFrame;

		return frames[actualFrame];
	}
};

#endif