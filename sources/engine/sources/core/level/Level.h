#pragma once

#include "input/Controllable.h"
#include "level/LevelData.h"
#include "level/GridSector.h"
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
	void PreDraw();
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
	Sector* GetSectorAtIndex(unsigned int x, unsigned int y);
	void ComputeObjectToGridMapping(const Rectangle& objectRect, int& outTopIndex, int& outLeftIndex, int& outBottomIndex, int& outRightIndex);
	bool IsAreaOutOfBounce(const float outTopIndex, const float outLeftIndex, const float outBottomIndex, const float outRightIndex);
	void RemoveObject(int index);
#if(DEBUG_SECTION)
	GameObject* GetGridRectObject(int x, int y);

	bool IsGridRectVisible(int x, int y);
	void SetGridRectVisibility(int x, int y, bool visibility);

	void AddVisibleGridLines();
	void RemoveVisibleGridLines();
	void RenderSectorDebugColor();
#endif

private:

	Logging log;

	// Level has ownership over the objects so the objects
	// will be deleted by the the Level
	FastAccessCollection<GameObject> sceneObjectsCollection;

	std::multimap<float, int> sceneRenderingObjects;

	std::vector<std::vector<std::unique_ptr<Sector>>> m_gameWorldGrid;
	Camera* activeLevelCamera;
	std::unordered_map<std::string, std::unique_ptr<Camera>> availableCameras;

#if(DEBUG_SECTION)	
	// This creates a grid of GameRectangles.
	// The boolean tells us if a certain object needs to be updated and rendered
	std::vector<std::vector<std::pair<std::unique_ptr<GameObject>, bool>>> m_gridRect;

	// Contains the grid lines
	std::vector<std::unique_ptr<GameObject>> sceneGridLines;

	bool isGridDrawingEnabled = true;
	bool isSectorColorRenderEnabled = true;
	bool isOutlineEnabled = true;
#endif
};