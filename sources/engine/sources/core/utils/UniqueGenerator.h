#pragma once
#include <set>
#include <stack>
#include <string>

class UniqueGenerator
{
	private:

		UniqueGenerator() {};

		UniqueGenerator(const UniqueGenerator&) = delete;
		UniqueGenerator& operator=(const UniqueGenerator&) = delete;

	public:

		static UniqueGenerator& Instance();

		std::string GenerateUniqueID();
		void RemoveID(const std::string id);
		void AddIDToMemory(const std::string id);

	private:

		unsigned int nextID = 0;
		std::set<std::string> generatedIds;
		std::stack<std::string> recycledIds;
};