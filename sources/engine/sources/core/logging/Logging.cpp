#include "Logging.h"
#include <ctime>
#include <chrono>
#include <algorithm>

Logging::Logging(const std::string& currentClassName) : className(currentClassName)
{

}

void Logging::message(const std::string& msg, Type type)
{
	message(msg.c_str(), type);
}

void Logging::message(const char* msg, Type type)
{
	switch (type)
	{
		case MSG_INFO:
		{
			constructAndPrintMessage(msg, "INFO");
			break;
		}
		case MSG_ERROR:
		{
			constructAndPrintMessage(msg, "ERROR");
			break;
		}
		case MSG_DEBUG:
		{
#if(DEBUG_SECTION)
			constructAndPrintMessage(msg, "DEBUG");
#endif
			break;
		}
		default:
			break;
	}
}

void Logging::constructAndPrintMessage(const char* msg, const std::string& type)
{
	// Get current date and time
	auto clock = std::chrono::system_clock::now();
	std::time_t clock_time = std::chrono::system_clock::to_time_t(clock);
	std::string time = std::ctime(&clock_time);

	// Remove new line
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

	std::cout << "[" << time << "]" << "[" << type << "][" << className << "]: " << msg << std::endl;
}