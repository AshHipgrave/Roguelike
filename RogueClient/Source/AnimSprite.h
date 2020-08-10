#pragma once

#include <map>

#include "Sprite.h"

struct AnimationFrame
{
	// Width of the frame on the texture atlas
	int Width = 0;

	// Height of the frame on the texture atlas
	int Height = 0;

	// X Position of the frame on the texture atlas
	int X = 0;

	// Y Position of the frame on the texture atlas
	int Y = 0;
};

struct Animation
{
	// Number of frames in the animation
	int FrameCount = 0;

	// FPS the animation should be played at (Each animation frame will be displayed for this number of render frames before it's changed for the next frame)
	float FramesPerSecond = 30.0f;

	// Frames that make up the animation and will be drawn to screen
	AnimationFrame* Frames = nullptr;
};

class AnimSprite : public Sprite
{
public:
	AnimSprite(std::string imagePath, std::map<std::string, Animation> animations, std::string startState, int width, int height, int x, int y);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SetState(std::string state);
	std::string GetState() const;

	void SetIdle(bool isIdle);

	void Reset();

private:
	// Is the animation currently 'idle' or paused?
	bool m_bIsIdle = false;

	// The current animation state being drawn
	std::string m_CurrentState;

	// The current frame being renderered
	int m_CurrentFrameIdx = 0;

	// FPS the animation plays at (After this number of frames we move to the next animation frame)
	float m_AnimFPS = 30.0f;

	// Number of frames the current sprite frame has been displayed for
	int m_CurrentFrameDrawCount = 0;

	// List of animations this sprite has. Sprites can have one or more animation 'states' identified by a string (e.g. 'Jump', 'Run' etc)
	std::map<std::string, Animation> m_SpriteAnimations;

	// Clipping rectangle to only draw the relevant portion of the sprite
	SDL_Rect m_FrameRect = { 0, 0, 0, 0 };
};