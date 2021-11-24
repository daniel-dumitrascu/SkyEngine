#include "Tile.h"

Tile::Tile(unsigned int rowIndex, unsigned int columnIndex)
	: m_gridRowIndex(rowIndex), m_gridColumnIndex(columnIndex)
{
	// What's very important here to remember is that the rectangle of this tile has
	// a generic position in the [-1, 1] coordonate system. The actual position in game world
	// will be optain by getting the GameRectangle's position
}

void Tile::RemoveCollidingObject(int id)
{
	std::map<int, GameObject*>::iterator foundIt = m_tileCollidingObjects.find(id);
	if(foundIt != m_tileCollidingObjects.end())
		m_tileCollidingObjects.erase(foundIt);
}

void Tile::AddCollidingObject(GameObject* obj)
{
	if (obj != nullptr)
		m_tileCollidingObjects.insert(std::pair<int, GameObject*>(obj->GetID(), obj));
}

bool Tile::HasCollidingObjects()
{
	return !m_tileCollidingObjects.empty();
}

const std::map<int, GameObject*>& Tile::GetCollidingObjects()
{
	return m_tileCollidingObjects;
}