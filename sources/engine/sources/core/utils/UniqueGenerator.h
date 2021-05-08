#pragma once
#include <set>
#include <stack>

class UniqueGenerator
{
	private:

		UniqueGenerator() {};

		UniqueGenerator(const UniqueGenerator&) = delete;
		UniqueGenerator& operator=(const UniqueGenerator&) = delete;

	public:

		static UniqueGenerator& Instance();

		unsigned int GenerateUniqueID();
		void RemoveID(const unsigned int id);

	private:

		unsigned int nextID = 0;
		std::set<int> generatedIds;
		std::stack<int> recycledIds;
};