#include "UniqueGenerator.h"

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

unsigned int UniqueGenerator::GenerateUniqueID()
{
	unsigned int id = 0;

	if (!recycledIds.empty())
	{
		id = recycledIds.top();
		recycledIds.pop();
		generatedIds.insert(id);
	}
	else if (nextID < UINT32_MAX)
	{
		id = ++nextID;
		generatedIds.insert(id);	
	}

	/*
	 * If nextID is equal with UINT32_MAX we will not be able to generate any more ids
	 * In that case we will need to wait for the recycle stack to "top" already created Ids
	 */

	return id;
}

void UniqueGenerator::RemoveID(const unsigned int id)
{
	const auto searchIdResult = generatedIds.find(id);

	if (searchIdResult != generatedIds.end())
	{
		recycledIds.push(*searchIdResult);
		generatedIds.erase(searchIdResult);
	}
}