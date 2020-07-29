#pragma once

#include <SDL.h>
#include <assert.h>

class GameTimer
{
public:
	GameTimer();

	float GetTotalTime() const;
	float GetDeltaTime() const;
	float GetFrequency() const;

	void Reset();

	void Start();
	void Stop();

	void Tick();

private:
	float m_DeltaTime;
	float m_Frequency;

	Uint64 m_StartTime;
	Uint64 m_StopTime;

	Uint64 m_CurrentTime;
	Uint64 m_PreviousTime;

	Uint64 m_TotalTime;

	bool m_bIsStopped;
};

