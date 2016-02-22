#include "timer.h"

bool Timer::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every second.
	m_ticksPerS = (float)(m_frequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}


void Timer::Frame()
{
	INT64 currentTime;
	float timeDifference;


	// Query the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate the difference in time since the last time we queried for the current time.
	timeDifference = (float)(currentTime - m_startTime);

	// Calculate the frame time by the time difference over the timer speed resolution.
	m_frameTime = timeDifference / m_ticksPerS;

	// Restart the timer.
	m_startTime = currentTime;

	return;
}



float Timer::GetTime()
{
	return m_frameTime;
}