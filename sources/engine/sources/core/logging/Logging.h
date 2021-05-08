#pragma once

#include <iostream>
#include <string>


class Logging
{
	public:
		enum Type
		{
			MSG_INFO,
			MSG_ERROR,
			MSG_DEBUG
		};

		Logging(const std::string& className);
		void message(const std::string& msg, Type type);
		void message(const char* msg, Type type);

	private:
		void constructAndPrintMessage(const char* msg, const std::string& type);

	private:
		std::string className;
};