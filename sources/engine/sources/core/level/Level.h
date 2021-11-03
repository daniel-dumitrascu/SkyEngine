#pragma once

#include "input/Controllable.h"
#include "level/LevelData.h"
#include "level/Tile.h"
#include "utils/FastAccessCollection.h"
#include "camera/Camera.h"
#include <unordered_map>
#include <map>

class Level: public Controllable
{
public:

	static Level* GetInstance();

	void Init();
	void Update();
	void Draw();

	void InputActionNotify(const InputEventBatch& inputBatch);
	
	Camera* GetActiveCamera() { return activeLevelCamera; }

private:

	Level();
	Level(const Level& copy) = delete;
	~Level();

	void CleanLevel();
	void ConstructLevel(LevelPackage* levelData);
	void ConstructGameGrid();
	Tile* GetTileAtIndex(unsigned int x, unsigned int y);
	void ComputeObjectToGridMapping(const Rectangle& objectRect, int& outTopIndex, int& outLeftIndex, int& outBottomIndex, int& outRightIndex);
	bool IsAreaOutOfBounce(const float outTopIndex, const float outLeftIndex, const float outBottomIndex, const float outRightIndex);
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
	std::map<std::string, GameObject*> sceneObjects;
	std::vector<std::vector<Tile*>> m_gameWorldGrid;
	Camera* activeLevelCamera; //TODO foloseste unique_ptr
	std::unordered_map<std::string, Camera*> availableCameras;

#if(DEBUG_SECTION)	
	// This creates a grid of GameRectangles.
	// The boolean tells us if a certain object needs to be updated and rendered
	std::vector<std::vector<std::pair<GameObject*, bool>>> m_gridRect;

	// This vector stored the ids of the lines used to draw the game grid
	std::vector<std::string> m_gridLinesIds;
	bool isGridDrawingEnabled = true;
	bool isColorTileRenderEnabled = true;
	bool isOutlineEnabled = true;
#endif
};