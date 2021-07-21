#ifndef CORE_TIME_H
#define CORE_TIME_H

#include <string>
#include "../logging/Logging.h"

namespace CoreTime
{
	extern Logging log;

	/* Util functions */
	unsigned long GetTime();

	std::string GetDateAndTimeAsString();

	class Timer
	{
		public:

			Timer() : m_previous_time(0),
				      m_update_interval(0.0f),
					  m_elapsed(0.0f) {};

			Timer(float update_interval) : m_previous_time(0),
				                           m_update_interval(update_interval),
										   m_elapsed(0.0) {};
			~Timer() {};

			void Start() { m_previous_time = CoreTime::GetTime(); };
			float GetElapsed() { return m_elapsed * 0.001f; }
			bool IsExceeded();
			
			Timer& operator=(float update_interval) 
			{ 
				m_update_interval = update_interval; 
				return (*this);
			}

		private:
			
			Timer(const Timer& copy) = delete;
			Timer& operator=(const Timer& copy) = delete;

		private:

			unsigned long m_previous_time;
			float m_update_interval;
			float m_elapsed;   /* elapsed time between frames in seconds */
	};
}

#endif