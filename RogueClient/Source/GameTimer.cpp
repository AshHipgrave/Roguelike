#include "GameTimer.h"

GameTimer::GameTimer()
{
	m_DeltaTime = -1;

	m_BaseTime = 0;
	m_PausedTime = 0;

	m_CurrentTime = 0;
	m_PreviousTime = 0;

	m_StoppedTime = 0;

	m_bIsStopped = false;

	m_Frequency = 1.0 / (double)SDL_GetPerformanceFrequency();
}

float GameTimer::GetTotalTime() const
{
	if (m_bIsStopped)
	{
		return (float)(((m_StoppedTime - m_PausedTime) - m_BaseTime) * m_Frequency);
	}

	return (float)(((m_CurrentTime - m_PausedTime) - m_BaseTime) * m_Frequency);
}

float GameTimer::GetDeltaTime() const
{
	return (float)m_DeltaTime;
}

void GameTimer::Reset()
{
	Uint64 currentTime = SDL_GetPerformanceCounter();

	m_BaseTime = currentTime;
	m_PreviousTime = currentTime;

	m_StoppedTime = 0;

	m_bIsStopped = false;
}

void GameTimer::Start()
{
	Uint64 startTime = SDL_GetPerformanceCounter();

	if (m_bIsStopped)
	{
		m_PausedTime += (startTime - m_StoppedTime);

		m_PreviousTime = startTime;
		m_StoppedTime = 0;

		m_bIsStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!m_bIsStopped)
	{
		Uint64 currentTime = SDL_GetPerformanceCounter();

		m_StoppedTime = currentTime;
	}
}

void GameTimer::Tick()
{
	if (m_bIsStopped)
	{
		m_DeltaTime = 0.0;
		return;
	}

	Uint64 currentTime = SDL_GetPerformanceCounter();
	m_CurrentTime = currentTime;

	m_DeltaTime = (m_CurrentTime - m_PreviousTime) * m_Frequency;

	m_PreviousTime = m_CurrentTime;

	if (m_DeltaTime < 0.0)
	{
		m_DeltaTime = 0.0;
	}
}
