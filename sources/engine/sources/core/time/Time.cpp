#include "Time.h"
#include <iostream>

#if(WINDOWS_PLATFORM)
#include <Windows.h>
#elif(LINUX_PLATFORM)
#include <time.h>
#include <math.h>
#endif

#include <ctime>

namespace CoreTime
{
	Logging log("Timer");
}

bool CoreTime::Timer::IsExceeded()
{
	static unsigned long curr_time;	

	curr_time = CoreTime::GetTime();
	m_elapsed = curr_time - m_previous_time;

	if (m_elapsed >= m_update_interval)
	{
		m_previous_time = curr_time;
		return true;
	}

	return false;
}

unsigned long CoreTime::GetTime()
{
#if(WINDOWS_PLATFORM)
	return GetTickCount();
#elif(LINUX_PLATFORM)
	struct timespec ts;
	if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0) {
		CoreTime::log.message("CoreTime::GetTime() - Problem in getting the time.", Logging::MSG_ERROR);
		return 0;
	}
	time_t seconds = ts.tv_sec;
	long miliseconds = round(ts.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds;
    if (miliseconds > 999) {
        seconds++;
        miliseconds = 0;
    }
	// Convert the whole result in milliseconds
	unsigned long result = (seconds * (uint64_t)1000) + miliseconds; 
	return result;
#endif
}

std::string CoreTime::GetDateAndTimeAsString()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d/%m/%Y %I:%M:%S", timeinfo);
	std::string str(buffer);

	return str;
}