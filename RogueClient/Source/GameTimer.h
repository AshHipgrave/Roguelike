#pragma once

#include <SDL.h>

class GameTimer
{
public:
	GameTimer();

	float GetTotalTime() const;
	float GetDeltaTime() const;

	void Reset();

	void Start();
	void Stop();

	void Tick();

private:
	double m_Frequency;
	double m_DeltaTime;

	Uint64 m_BaseTime;
	Uint64 m_PausedTime;
	Uint64 m_StoppedTime;
	Uint64 m_PreviousTime;
	Uint64 m_CurrentTime;
	
	bool m_bIsStopped;
};

