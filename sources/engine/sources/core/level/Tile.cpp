#include "Tile.h"

Tile::Tile(unsigned int rowIndex, unsigned int columnIndex, const Rectangle& rect)
	: m_gridRowIndex(rowIndex), m_gridColumnIndex(columnIndex), m_tileRectangle(rect)
{
	// What's very important here to remember is that the rectangle of this tile has
	// a generic position in the [-1, 1] coordonate system. The actual position in game world
	// will be optain by getting the GameRectangle's position
}

void Tile::RemoveCollidingObject(std::string& id)
{
	std::map<std::string, GameObject*>::iterator foundIt = m_tileCollidingObjects.find(id);
	if(foundIt != m_tileCollidingObjects.end())
		m_tileCollidingObjects.erase(foundIt);
}

void Tile::AddCollidingObject(GameObject* obj)
{
	if (obj != nullptr)
	{
		std::string label = obj->GetLabel().GetStrLabel();
		m_tileCollidingObjects.insert(std::pair<std::string, GameObject*>(label, obj));	
	}
}

bool Tile::HasCollidingObjects()
{
	return !m_tileCollidingObjects.empty();
}

const std::map<std::string, GameObject*>& Tile::GetCollidingObjects()
{
	return m_tileCollidingObjects;
}