#include "GameTimer.h"

#include <SDL.h>

GameTimer::GameTimer()
{
	m_StartTime = 0;
	m_StopTime = 0;
	m_TotalTime = 0;

	m_CurrentTime = 0;
	m_PreviousTime = 0;

	m_DeltaTime = 0.0f;

	m_bIsStopped = true;

	m_Frequency = (float)SDL_GetPerformanceFrequency();
}

float GameTimer::GetTotalTime() const
{
	return m_TotalTime;
}

float GameTimer::GetDeltaTime() const
{
	return m_DeltaTime;
}

float GameTimer::GetFrequency() const
{
	return m_Frequency;
}

void GameTimer::Reset()
{
	assert(m_bIsStopped);

	Uint64 currentTime = SDL_GetPerformanceCounter();

	m_StartTime = currentTime;

	m_StopTime = 0;
	m_TotalTime = 0;

	m_bIsStopped = false;
}

void GameTimer::Start()
{
	Reset();
}

void GameTimer::Stop()
{
	assert(!m_bIsStopped);

	m_StopTime = SDL_GetPerformanceCounter();

	m_bIsStopped = true;
}

void GameTimer::Tick()
{
	if (m_bIsStopped)
	{
		m_DeltaTime = 0.0f;
		return;
	}

	Uint64 currentTime = SDL_GetPerformanceCounter();
	m_CurrentTime = currentTime;
	
	m_DeltaTime = (m_CurrentTime - m_PreviousTime) / m_Frequency * 1000.0f;

	m_PreviousTime = m_CurrentTime;

	m_TotalTime = m_StartTime - m_CurrentTime;
}
