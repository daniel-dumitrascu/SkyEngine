#pragma once
#include <string>
#include <map>
#include "primitive/Rectangle.h"
#include "entities/GameObject.h"


class Tile
{
	public:

		Tile(unsigned int rowIndex, unsigned int columnIndex);

		int GetRowIndex() { return m_gridRowIndex; }
		int GetColumnIndex() { return m_gridColumnIndex; }
		void RemoveCollidingObject(std::string& id);
		void AddCollidingObject(GameObject* obj);
		bool HasCollidingObjects();
		const std::map<std::string, GameObject*>& GetCollidingObjects();

	private:

		/*
		 * The position of the file in the game matrix grid
		 */
		unsigned int m_gridRowIndex;
		unsigned int m_gridColumnIndex;

		/*
		 * A list of game objects that collide with this tile
		 */
		std::map<std::string, GameObject*> m_tileCollidingObjects;
};