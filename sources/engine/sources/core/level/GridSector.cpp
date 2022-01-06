#include "GridSector.h"

Sector::Sector(unsigned int rowIndex, unsigned int columnIndex)
	: m_gridRowIndex(rowIndex), m_gridColumnIndex(columnIndex)
{
	// What's very important here to remember is that the rectangle of this sector has
	// a generic position in the [-1, 1] coordonate system. The actual position in game world
	// will be optain by getting the GameRectangle's position
}

void Sector::RemoveCollidingObject(int id)
{
	std::map<int, GameObject*>::iterator foundIt = gridSectorCollidingObjects.find(id);
	if(foundIt != gridSectorCollidingObjects.end())
		gridSectorCollidingObjects.erase(foundIt);
}

void Sector::AddCollidingObject(GameObject* obj)
{
	if (obj != nullptr)
		gridSectorCollidingObjects.insert(std::pair<int, GameObject*>(obj->GetID(), obj));
}

bool Sector::HasCollidingObjects()
{
	return !gridSectorCollidingObjects.empty();
}

const std::map<int, GameObject*>& Sector::GetCollidingObjects()
{
	return gridSectorCollidingObjects;
}