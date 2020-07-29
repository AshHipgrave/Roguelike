#pragma once

#include <SDL.h>

class GameTimer
{
public:
	GameTimer();

	void Start();
	void Stop();

	void Pause();
	void Resume();

	Uint32 GetTicks();

	bool IsPaused() const;
	bool IsStarted() const;

private:
	Uint32 m_StartTicks = 0;
	Uint32 m_PausedTicks = 0;

	bool m_bIsStarted = false;
	bool m_bIsPaused = false;
};

