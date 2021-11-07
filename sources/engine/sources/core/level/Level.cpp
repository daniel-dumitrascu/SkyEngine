#include "Level.h"
#include "platform/input/InputManager.h"
#include "global/GlobalData.h"
#include "LevelLoader.h"
#include "LevelDefines.h"
#include "global/GlobalPaths.h"
#include "utils/Physics2D.h"
#include "video/Painter.h"
#include "actions/Actions.h"
#include "entities/GameObjectFactory.h"

#if(DEBUG_SECTION)
#include "primitive/GameRectangle.h"
#endif

Level* Level::GetInstance()
{
	static Level s_level;
	return &s_level;
}

Level::Level() : log("Level"), Controllable(INPUT_HANDLE_PROFILE_LEVEL)
{
	int subId = InputManager::GetInstance()->AddSubscriber((Controllable*)this);
	if (subId == -1)
	{
		std::cout << "[ERROR] Problem when addind the level as subscriber" << std::endl;
	}
	else
		((Controllable*)this)->SetSubscriberId(subId);
}

Level::~Level()
{
	CleanLevel();
}

void Level::CleanLevel()
{
	// Remove all the cameras from the level
	availableCameras.clear();
	activeLevelCamera = nullptr;

	// Remove all the entities from the level 
	for (auto& mapEntry : sceneObjects)
	{
		delete mapEntry.second;
		mapEntry.second = nullptr;
	}

	sceneObjects.clear();

	// Deallocate the game rectangles
#if(DEBUG_SECTION)
	for (int i = 0; i < m_gridRect.size(); ++i)
		for (int j = 0; j < m_gridRect[i].size(); ++j)
			delete m_gridRect[i][j].first;
#endif

	// Deallocate the grid structure
	for (int i = 0; i < m_gameWorldGrid.size(); ++i)
		for (int j = 0; j < m_gameWorldGrid[i].size(); ++j)
			delete m_gameWorldGrid[i][j];


	// Reset score and other settings
	//TODO to implement
}

void Level::ConstructLevel(LevelPackage* levelData)
{
	GameObject* obj;
	int outTopIndex = 0;
	int outLeftIndex = 0;
	int outBottomIndex = 0;
	int outRightIndex = 0;

	InputManager* input_manager = InputManager::GetInstance();
	
	// Create the scene cameras
	for (std::list<CameraPackage>::iterator cameraIte = levelData->m_level_cameras.begin(); cameraIte != levelData->m_level_cameras.end(); ++cameraIte)
	{
		Camera* camera = GameObjectFactory::GetInstance()->CreateCamera((*cameraIte));
		availableCameras.insert(std::make_pair(cameraIte->camera_id, camera));
	}

	auto ite = availableCameras.find(levelData->m_active_camera_id);
	if (ite != availableCameras.end())
		activeLevelCamera = ite->second.get();
	else
	{
		log.message("Selected camera is not available, application will terminate", Logging::MSG_ERROR);
		exit(0);	//TODO at the moment this is fine but the failing of loading a scene should not terminate the whole app
	}
	
	// Create scene objects
	for (std::list<GameObjectPackage>::iterator objectIte = levelData->m_level_data.begin(); objectIte != levelData->m_level_data.end(); ++objectIte)
	{
		obj = GameObjectFactory::GetInstance()->CreateGameObject((*objectIte));
		if (obj)
		{
			if (obj->GetID().compare(levelData->m_active_camera_attached_object) == 0)
			{
				activeLevelCamera->AttachCameraToObject(obj);
			}

			sceneObjects.insert(std::pair<std::string, GameObject*>(obj->GetID(), obj));

			if (obj->IsFlagON(OBJECT_IS_CONTROLLABLE))
			{
				int subId = input_manager->AddSubscriber((Controllable*)obj);
				if (subId == -1)
				{
					std::cout << "[ERROR] Problem when addind an object as subscriber" << std::endl;
					continue;
				}
				else
					((Controllable*)obj)->SetSubscriberId(subId);
			}
		}
		else
		{
			log.message("Can't construct level, not enough resources.", Logging::MSG_ERROR);
		}
	}

	ConstructGameGrid();

#if(DEBUG_SECTION)
	if (isGridDrawingEnabled)
		AddVisibleGridLines();
#endif

	for (auto& mapEntry : sceneObjects)
	{
		// Calculation  of the object in tile map
		Rectangle objRect = mapEntry.second->GetObjectWorldRect();
		ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);
		mapEntry.second->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

		// Add the object in every tile with which it intersects
		for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
			for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
			{
				Tile* newTile = GetTileAtIndex(xAxisIndex, yAxisIndex);
				newTile->AddCollidingObject(mapEntry.second);
#if(DEBUG_SECTION)
				// Activate the visibility on the new area
				SetGridRectVisibility(xAxisIndex, yAxisIndex, true);
				GetGridRectObject(xAxisIndex, yAxisIndex)->Update();
#endif
			}
	}
}

void Level::ConstructGameGrid()
{
#if(DEBUG_SECTION)
	vec_4x color;
	vector::vector_4x::SetVector(color, 0.0f, 1.0f, 0.0f, 1.0f);
#endif

	// Resize the row count of the grid
	m_gameWorldGrid.resize(WORLD_GRID_HEIGHT_COUNT);
#if(DEBUG_SECTION)
	m_gridRect.resize(WORLD_GRID_HEIGHT_COUNT);
#endif

	vec_2x leftTop(-(WORLD_TILE_WIDTH / 2.0f), WORLD_TILE_HEIGHT / 2.0f);
	vec_2x rightBottom(WORLD_TILE_WIDTH / 2.0f, -(WORLD_TILE_HEIGHT / 2.0f));
	Rectangle genericRect(leftTop, rightBottom);

	for (unsigned int i = 0; i < WORLD_GRID_HEIGHT_COUNT; ++i)
	{
		// Resize each row by the number of column
		m_gameWorldGrid[i].resize(WORLD_GRID_WIDTH_COUNT);
#if(DEBUG_SECTION)
		m_gridRect[i].resize(WORLD_GRID_WIDTH_COUNT);
#endif

		// Iterate in the new allocated row and create new tiles
		for (unsigned int j = 0; j < WORLD_GRID_WIDTH_COUNT; ++j)
		{
			m_gameWorldGrid[i][j] = new Tile(i, j, genericRect);   //TODO - does a Tile need a Rect?

			// After we have constructed the game grid we must create GameRect objects 
			// for each time so that we can use them in the debug mode of the app
#if(DEBUG_SECTION)
			int xPos = (WORLD_TILE_WIDTH * j) + WORLD_TILE_WIDTH / 2;
			int yPos = (WORLD_TILE_HEIGHT * i) + WORLD_TILE_HEIGHT / 2;

			m_gridRect[i][j] = std::make_pair(GameObjectFactory::GetInstance()->CreateGameRectangle(genericRect, xPos, yPos, color), false);
#endif
		}
	}
}

#if(DEBUG_SECTION)

void Level::AddVisibleGridLines()
{
	vec_4x lineColor;
	vec_2x startPoint;
	vec_2x endPoint;

	vector::vector_4x::SetVector(lineColor, 0.0f, 0.5f, 0.5f, 1.0f);
	GameObject* gameLine = nullptr;

	// Horizontal lines
	for (int gridHeightIndex = 0; gridHeightIndex < WORLD_GRID_HEIGHT_COUNT; ++gridHeightIndex)
	{
		vector::vector_2x::SetVector(startPoint, 0.0f, WORLD_TILE_HEIGHT * gridHeightIndex);
		vector::vector_2x::SetVector(endPoint, WORLD_TILE_WIDTH * WORLD_GRID_WIDTH_COUNT, WORLD_TILE_HEIGHT * gridHeightIndex);

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);
		sceneObjects.insert(std::pair<std::string, GameObject*>(gameLine->GetID(), gameLine));
		m_gridLinesIds.push_back(gameLine->GetID());
	}

	// Vertical lines
	for (int gridWidthIndex = 0; gridWidthIndex < WORLD_GRID_WIDTH_COUNT; ++gridWidthIndex)
	{
		vector::vector_2x::SetVector(startPoint, WORLD_TILE_WIDTH * gridWidthIndex, 0.0f);
		vector::vector_2x::SetVector(endPoint, WORLD_TILE_WIDTH * gridWidthIndex, WORLD_TILE_HEIGHT * WORLD_GRID_HEIGHT_COUNT);

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);
		sceneObjects.insert(std::pair<std::string, GameObject*>(gameLine->GetID(), gameLine));
		m_gridLinesIds.push_back(gameLine->GetID());
	}
}

void Level::RemoveVisibleGridLines()
{
	for (int i = 0; i < m_gridLinesIds.size(); ++i)
	{
		auto ite = sceneObjects.find(m_gridLinesIds[i]);
		if (ite != sceneObjects.end())
		{
			delete ite->second;
			sceneObjects.erase(ite);
		}
	}

	m_gridLinesIds.clear();
}

void Level::RenderTileDebugColor()
{
	for (int i = 0; i < m_gridRect.size(); ++i)
	{
		for (int j = 0; j < m_gridRect[i].size(); ++j)
		{
			if (m_gridRect[i][j].second == true) // if the visibility is set
			{
				m_gridRect[i][j].first->PreDraw();
				m_gridRect[i][j].first->Draw();
			}
		}
	}
}

#endif

void Level::Init()
{
	// We do a level cleanup before populating 
	// the level with the new data 
	CleanLevel();

	// Load the level data
	LevelPackage* levelData = (LevelPackage*)LevelLoader::GetInstance()->Load(levels_path + LEVEL_1);

	// Create the entities for this level
	ConstructLevel(levelData);

	delete levelData;
}

void Level::Update()
{
	int outTopIndex = 0;
	int outLeftIndex = 0;
	int outBottomIndex = 0;
	int outRightIndex = 0;
	bool isAlreadyReset = false;
	bool isMovementInCurrUpdate = false;

#if(DEBUG_SECTION)
	vec_4x green;
	vector::vector_4x::SetVector(green, 0.0f, 1.0f, 0.0f, 1.0f);
#endif

	for (std::map<std::string, GameObject*>::iterator sceneIte = sceneObjects.begin(); 
		sceneIte != sceneObjects.end();
		++sceneIte)
	{
		if (!sceneIte->second->IsAlive())
		{
			sceneIte = sceneObjects.erase(sceneIte);
			continue;
		}

		sceneIte->second->Update();
		if (sceneIte->second->IsFlagON(OBJECT_IS_MOVING))
		{
			isMovementInCurrUpdate = true;
#if(DEBUG_SECTION)
			//TODO - oare acest cod poate fi executat in afara for-ului?
			if (!isAlreadyReset)
			{
				// Reset the color on all tile objects to green
				isAlreadyReset = true;
				for (unsigned int i = 0; i < WORLD_GRID_HEIGHT_COUNT; ++i)
					for (unsigned int j = 0; j < WORLD_GRID_WIDTH_COUNT; ++j)
					{
						((GameRectangle*)(m_gridRect[i][j].first))->SetColor(green);
					}
			}
#endif
			// Get the old area values and remove the object pointer from each tile
			std::array<int, 4> oldGridMapping = sceneIte->second->GetOccupiedGriDArea();

			// Check if the old occupied grid area is not out of bounce
			if (!IsAreaOutOfBounce(oldGridMapping[0], oldGridMapping[1], oldGridMapping[2], oldGridMapping[3]))
			{
				for (int yAxisIndex = oldGridMapping[0]; yAxisIndex >= oldGridMapping[2]; yAxisIndex--)
					for (int xAxisIndex = oldGridMapping[1]; xAxisIndex <= oldGridMapping[3]; xAxisIndex++)
					{
						Tile* oldTile = GetTileAtIndex(xAxisIndex, yAxisIndex);

						std::string label = sceneIte->second->GetID();
						oldTile->RemoveCollidingObject(label); //TODO pt consistenta, aceasta metoda trebuie sa ia tot un Object
#if(DEBUG_SECTION)
						if (!oldTile->HasCollidingObjects())
						{
							// Deactivate the visibility on the old area
							SetGridRectVisibility(xAxisIndex, yAxisIndex, false);
						}
#endif
					}
			} 

			// Remove the old colliding neighbours
			sceneIte->second->ClearCollidingNeighbours();

			// Get the rectangle of the game object and calculate the occupied area in the grid
			Rectangle objRect = sceneIte->second->GetObjectWorldRect();
			ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

			// Check if the new occupied grid area is not out of bounce
			if (!IsAreaOutOfBounce(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex))
			{
				// Add the game object pointer to the new tiles and construct new colliding neighbours
				sceneIte->second->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

				for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
					for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
					{
						Tile* newTile = GetTileAtIndex(xAxisIndex, yAxisIndex);
						const std::map<std::string, GameObject*> collidingObj = newTile->GetCollidingObjects();
						std::map<std::string, GameObject*>::const_iterator ite = collidingObj.begin();
						for (; ite != collidingObj.end(); ite++)
						{
							sceneIte->second->AddCollidingNeighbour(ite->second);
							ite->second->AddCollidingNeighbour(sceneIte->second);
						}

						newTile->AddCollidingObject(sceneIte->second);
#if(DEBUG_SECTION)
						// Activate the visibility on the new area
						SetGridRectVisibility(xAxisIndex, yAxisIndex, true);
#endif
					}
			}

			// Check if object is colliding with other objects from scene
			const std::map<const std::string, GameObject*> collidingNeighbours = sceneIte->second->GetCollidingNeighbours();
			std::map<const std::string, GameObject*>::const_iterator ite = collidingNeighbours.begin();
			for (; ite != collidingNeighbours.end(); ite++)
			{
				//TODO we should use a general collision detection here that implements something like CollisionDetectionAABB
				//TODO dependency injection
				bool isColliding = Physics2D::CollisionDetectionAABB(objRect, ite->second->GetObjectWorldRect());
				if (isColliding)
				{
#if(DEBUG_SECTION)
					// Color in red the tiles occupied by the objects that are colliding 
					vec_4x color;
					vector::vector_4x::SetVector(color, 1.0f, 0.0f, 0.0f, 1.0f);

 					std::array<int, 4> objectAGridMapping = sceneIte->second->GetOccupiedGriDArea();
					std::array<int, 4> objectBGridMapping = ite->second->GetOccupiedGriDArea();

					for (int yAxisIndex = objectAGridMapping[0]; yAxisIndex >= objectAGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectAGridMapping[1]; xAxisIndex <= objectAGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first))->SetColor(color);
						}

					for (int yAxisIndex = objectBGridMapping[0]; yAxisIndex >= objectBGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectBGridMapping[1]; xAxisIndex <= objectBGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first))->SetColor(color);
						}

						std::cout << "Collision between <" << sceneIte->second->GetID() << "> and <" << ite->second->GetID() << ">" << std::endl;
#endif
				}
			}
		}
		// This is necessary so that we don't "forget" about the objects that are in collision
		// but they haven't moved this frame. This is just for the debug red coloring that is being lost
		// when collision objects aren't moved in future frames.
		// Here, we just recolor them in red
#if(DEBUG_SECTION)
		else
		{
			// Check if object is colliding with other objects from scene
			const std::map<const std::string, GameObject*> collidingNeighbours = sceneIte->second->GetCollidingNeighbours();
			std::map<const std::string, GameObject*>::const_iterator ite = collidingNeighbours.begin();
			for (; ite != collidingNeighbours.end(); ite++)
			{
				Rectangle objRect = sceneIte->second->GetObjectWorldRect();
				bool isColliding = Physics2D::CollisionDetectionAABB(objRect, ite->second->GetObjectWorldRect());
				if (isColliding)
				{
					// Color in red the tiles occupied by the objects that are colliding
					vec_4x color;
					vector::vector_4x::SetVector(color, 1.0f, 0.0f, 0.0f, 1.0f);

					std::array<int, 4> objectAGridMapping = sceneIte->second->GetOccupiedGriDArea();
					std::array<int, 4> objectBGridMapping = ite->second->GetOccupiedGriDArea();

					for (int yAxisIndex = objectAGridMapping[0]; yAxisIndex >= objectAGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectAGridMapping[1]; xAxisIndex <= objectAGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first))->SetColor(color);
						}

					for (int yAxisIndex = objectBGridMapping[0]; yAxisIndex >= objectBGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectBGridMapping[1]; xAxisIndex <= objectBGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first))->SetColor(color);
						}
				}
			}
		}
#endif
	}

	if (isMovementInCurrUpdate)
	{
		// Update the debug grid when movement has been detected in the current update frame
		for (int i = 0; i < m_gridRect.size(); ++i)
			for (int j = 0; j < m_gridRect[i].size(); ++j)
			{
				m_gridRect[i][j].first->Update();
			}
	}
}

void Level::Draw()
{
	// Clear the color buffer
	Painter::ClearScreen();

#if(DEBUG_SECTION)
	if(isColorTileRenderEnabled)
		RenderTileDebugColor();
#endif

	// Draw all the level entities
	for (const auto& sceneEntry : sceneObjects)
	{
		sceneEntry.second->PreDraw();
		sceneEntry.second->Draw();
	}
}

void Level::InputActionNotify(const InputEventBatch& inputBatch)
{
	int const batchSize = inputBatch.getDataBatchSize();
	if (batchSize > 0)
	{
		for (int i = 0; i < batchSize; ++i)
		{
			const DataBindingWrapper* wrapper = inputToActionBindings->GetBinding(inputBatch.getDataAtIndex(i));
			if (wrapper == nullptr)
				continue;

			if (wrapper->action == Actions::Game::GAME_EXIT)
			{
				exit(0); //TODO here should be a new state for closing
				break;
			}
#if(DEBUG_SECTION)
			else if (wrapper->action == Actions::Debug::DEBUG_GRID_DRAW)
			{
				isGridDrawingEnabled = !isGridDrawingEnabled;
				if (isGridDrawingEnabled)
					AddVisibleGridLines();
				else
					RemoveVisibleGridLines();
			}
			else if (wrapper->action == Actions::Debug::DEBUG_OBJECT_TILE_MAPPING)
			{
				isColorTileRenderEnabled = !isColorTileRenderEnabled;
			}
			else if (wrapper->action == Actions::Debug::DEBUG_OBJECT_RECTANGLE)
			{
				isOutlineEnabled = !isOutlineEnabled;

				// All the renderable objects in the scene must get the new value
				for (auto sceneObj : sceneObjects)
				{
					if (sceneObj.second->IsAlive() && sceneObj.second->IsFlagON(OBJECT_IS_RENDERABLE))
						sceneObj.second->SetOutline(isOutlineEnabled);
				}
			}
#endif
		}
	}
}

Tile* Level::GetTileAtIndex(unsigned int x, unsigned int y)
{
	return (x < m_gameWorldGrid.size() && y < m_gameWorldGrid[x].size()) ? m_gameWorldGrid[x][y] : nullptr;
}

void Level::ComputeObjectToGridMapping(const Rectangle& objectRect, int& outTopIndex, int& outLeftIndex, int& outBottomIndex, int& outRightIndex)
{
	static float worldTileWidthFloat = (float)WORLD_TILE_WIDTH;
	static float worldTileHeightFloat = (float)WORLD_TILE_HEIGHT;

	// Part 1: For every top, bottom, left and right we calculate the index
	float tempObjectTopGridIndex = objectRect.GetTop() / worldTileHeightFloat;
	float tempObjectBottomGridIndex = objectRect.GetBottom() / worldTileHeightFloat;
	float tempObjectLeftGridIndex = objectRect.GetLeft() / worldTileWidthFloat;
	float tempObjectRightGridIndex = objectRect.GetRight() / worldTileWidthFloat;

	// Part 2: We add +1 for top and left
	outTopIndex = (int)tempObjectTopGridIndex;
	outLeftIndex = (int)tempObjectLeftGridIndex;
	outBottomIndex = (int)tempObjectBottomGridIndex;
	outRightIndex = (int)tempObjectRightGridIndex;

	// Part 3: We add +1 for top and right only if modulo of multiplier if non-zero
	if (std::fmod(objectRect.GetTop(), worldTileHeightFloat) == 0.0f)
		--outTopIndex;

	if (std::fmod(objectRect.GetRight(), worldTileWidthFloat) == 0.0f)
		--outRightIndex;
}

bool Level::IsAreaOutOfBounce(const float outTopIndex, const float outLeftIndex, const float outBottomIndex, const float outRightIndex)
{
	return (outTopIndex < 0 || outTopIndex >= WORLD_GRID_HEIGHT_COUNT) ||
		   (outBottomIndex < 0 || outBottomIndex >= WORLD_GRID_HEIGHT_COUNT) ||
		   (outLeftIndex < 0 || outLeftIndex >= WORLD_GRID_WIDTH_COUNT) ||
		   (outRightIndex < 0 || outRightIndex >= WORLD_GRID_WIDTH_COUNT);
}

#if(DEBUG_SECTION)
GameObject* Level::GetGridRectObject(int x, int y)
{
	// y - row
	// x - column

	if (y >= m_gridRect.size())
		return nullptr;

	if (x >= m_gridRect[y].size())
		return nullptr;

	return m_gridRect[y][x].first;
}

bool Level::IsGridRectVisible(int x, int y)
{
	// y - row
	// x - column

	//TODO error message here
	if (y >= m_gridRect.size())
		return false;

	//TODO error message here
	if (x >= m_gridRect[y].size())
		return false;

	return m_gridRect[y][x].second;
}

void Level::SetGridRectVisibility(int x, int y, bool visibility)
{
	// y - row
	// x - column

	//TODO error message here
	if (y >= m_gridRect.size())
		return;

	//TODO error message here
	if (x >= m_gridRect[y].size())
		return;

	m_gridRect[y][x].second = visibility;
}
#endif