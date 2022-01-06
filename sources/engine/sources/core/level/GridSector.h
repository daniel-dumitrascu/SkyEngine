#pragma once
#include <string>
#include <map>
#include "primitive/Rectangle.h"
#include "entities/GameObject.h"


class Sector
{
	public:

		Sector(unsigned int rowIndex, unsigned int columnIndex);

		int GetRowIndex() { return m_gridRowIndex; }
		int GetColumnIndex() { return m_gridColumnIndex; }
		void RemoveCollidingObject(int id);
		void AddCollidingObject(GameObject* obj);
		bool HasCollidingObjects();
		const std::map<int, GameObject*>& GetCollidingObjects();

	private:

		/*
		 * The position of the file in the game matrix grid
		 */
		unsigned int m_gridRowIndex;
		unsigned int m_gridColumnIndex;

		/*
		 * A list of game objects that collide with this sector
		 */
		std::map<int, GameObject*> gridSectorCollidingObjects;
};