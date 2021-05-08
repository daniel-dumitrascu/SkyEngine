#ifndef LEVEL_GAME
#define LEVEL_GAME

//#include "geometry/baching/DrawScheme.h"

#include "../game_objects/Background.h"
#include "../game_objects/Player.h"
#include "../game_objects/Bird.h"
#include "../game_objects/StaticObject.h"
#include "../game_objects/Soldier.h"
#include "input/Controllable.h"
#include "level/LevelData.h"
#include "level/Tile.h"
#include "utils/FastAccessCollection.h"
#include "logging/Logging.h"
#include <vector>
#include <list>



class Level : public Controllable //public DrawScheme
{
	public:

		static Level* GetInstance();

		void Init();
		void Update();
		void Draw();

		void InputActionNotify(const InputEventBatch& inputBatch);

	private:

		Level();
		Level(const Level& copy) = delete;
		~Level();

		void CleanLevel();
		void ConstructLevel(LevelPackage* levelData);
		void ConstructGameGrid();
		Tile* GetTileAtIndex(unsigned int x, unsigned int y);
		void ComputeObjectToGridMapping(const Rectangle& objectRect, int& outTopIndex, int& outLeftIndex, int& outBottomIndex, int& outRightIndex);
		Tile* GetGridTile(int x, int y);
		void RemoveObject(int index);
#if(DEBUG_SECTION)
		GameObject* GetGridRectObject(int x, int y);
		
		bool IsGridRectVisible(int x, int y);
		void SetGridRectVisibility(int x, int y, bool visibility);

		void AddVisibleGridLines();
		void RemoveVisibleGridLines();
		void RenderTileDebugColor();
#endif

	private:

		Logging log;

		// Level has ownership over the objects so the objects
		// will be deleted by the the Level
		FastAccessCollection <GameObject*> m_sceneObjects;
		std::vector<std::vector<Tile*>> m_gameWorldGrid;

#if(DEBUG_SECTION)	
		// This creates a grid of GameRectangles.
		// The boolean tells us if a certain object needs to be updated and rendered
		std::vector<std::vector<std::pair<GameObject*, bool>>> m_gridRect;

		// This vector stored the ids of the lines used to draw the game grid
		std::vector<int> m_gridLinesIds;
		bool isGridDrawingEnabled = true;
		bool isColorTileRenderEnabled = true;
		bool isOutlineEnabled = true;
#endif
};

#endif