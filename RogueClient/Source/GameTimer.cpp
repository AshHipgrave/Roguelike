#include "GameTimer.h"

#include <iostream>

GameTimer::GameTimer()
{
	m_StartTicks = 0;
	m_PausedTicks = 0;

	m_bIsStarted = false;
	m_bIsPaused = false;
}

void GameTimer::Start()
{
	if (m_bIsStarted)
	{
		std::cout << "WARNING: Attempt to start an already running timer! If the timer is paused, use GameTimer::Resume() to restart it." << std::endl;
		return;
	}

	m_bIsStarted = true;
	m_bIsPaused = false;

	m_StartTicks = SDL_GetTicks();
	m_PausedTicks = 0;
}

void GameTimer::Stop()
{
	m_bIsStarted = false;
	m_bIsPaused = false;

	m_StartTicks = 0;
	m_PausedTicks = 0;
}

void GameTimer::Pause()
{
	if (!m_bIsStarted || m_bIsPaused)
	{
		std::cout << "WARNING: Attempt to pause a non-running or already paused timer!" << std::endl;
		return;
	}

	m_bIsPaused = true;

	m_PausedTicks = SDL_GetTicks() - m_StartTicks;
	m_StartTicks = 0;
}

void GameTimer::Resume()
{
	if (!m_bIsStarted || !m_bIsPaused)
	{
		std::cout << "WARNING: Attempt to resume a non-running or non-paused timer!" << std::endl;
		return;
	}

	m_bIsPaused = false;

	m_StartTicks = SDL_GetTicks() - m_PausedTicks;
	m_PausedTicks = 0;
}

Uint32 GameTimer::GetTicks()
{
	if (m_bIsStarted)
	{
		if (m_bIsPaused)
		{
			return m_PausedTicks;
		}

		return SDL_GetTicks() - m_StartTicks;
	}

	return 0;
}

bool GameTimer::IsPaused() const
{
	return m_bIsPaused;
}

bool GameTimer::IsStarted() const
{
	return m_bIsStarted;
}
