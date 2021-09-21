#include "UniqueGenerator.h"
#include <iostream>

#if(WINDOWS_PLATFORM)
	#include <limits.h>
#elif(LINUX_PLATFORM)
	#include <stdint.h>
#endif

UniqueGenerator& UniqueGenerator::Instance()
{
	static UniqueGenerator instance;
	return instance;
}

std::string UniqueGenerator::GenerateUniqueID()
{
	std::string id = "";

	if (!recycledIds.empty())
	{
		id = recycledIds.top();
		recycledIds.pop();
		generatedIds.insert(id);
	}
	else if (nextID < UINT32_MAX)
	{
		id = std::to_string(++nextID);
		generatedIds.insert(id);
	}

	/*
	 * If nextID is equal with UINT32_MAX we will not be able to generate any more ids
	 * In that case we will need to wait for the recycle stack to "top" already created Ids
	 */

	return id;
}

void UniqueGenerator::RemoveID(const std::string id)
{
	const auto searchIdResult = generatedIds.find(id);

	if (searchIdResult != generatedIds.end())
	{
		recycledIds.push(*searchIdResult);
		generatedIds.erase(searchIdResult);
	}
}

void UniqueGenerator::AddIDToMemory(const std::string id)
{
	auto ite = generatedIds.insert(id);
	if (ite.second = false)
	{
		std::cout << "ID <" << id << "> is already generated";
	}
}