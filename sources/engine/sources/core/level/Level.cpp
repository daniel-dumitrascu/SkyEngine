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
	for (int index = 0; index < sceneObjectsCollection.Count(); ++index)
	{
		if (!sceneObjectsCollection.IsSlotFree(index))
			RemoveObject(index);
	}

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
			int objUniqueID = sceneObjectsCollection.Occupy(obj);
			obj->SetID(objUniqueID);
			objectIte->m_sceneID = objUniqueID;

			if (objectIte->m_id.compare(levelData->m_active_camera_attached_object) == 0)
			{
				activeLevelCamera->AttachCameraToObject(obj);
			}		

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

	for (int index = 0; index < sceneObjectsCollection.Count(); ++index)
	{
		// Calculation of the object in grid sector
		Rectangle objRect = sceneObjectsCollection.Retrive(index)->GetObjectWorldRect();
		ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);
		sceneObjectsCollection.Retrive(index)->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

		// Add the object in every sector with which it intersects
		for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
			for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
			{
				Sector* newSector = GetSectorAtIndex(xAxisIndex, yAxisIndex);
				newSector->AddCollidingObject(sceneObjectsCollection.Retrive(index));
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

	for (unsigned int i = 0; i < WORLD_GRID_HEIGHT_COUNT; ++i)
	{
		// Resize each row by the number of column
		m_gameWorldGrid[i].resize(WORLD_GRID_WIDTH_COUNT);
#if(DEBUG_SECTION)
		m_gridRect[i].resize(WORLD_GRID_WIDTH_COUNT);
#endif

		// Iterate in the new allocated row and create new sectors
		for (unsigned int j = 0; j < WORLD_GRID_WIDTH_COUNT; ++j)
		{
			m_gameWorldGrid[i][j] = std::make_unique<Sector>(i, j);

			// After we have constructed the game grid we must create GameRect objects 
			// for each time so that we can use them in the debug mode of the app
#if(DEBUG_SECTION)
			vec_2x recLeftTop(GRID_SECTOR_WIDTH * j, (GRID_SECTOR_HEIGHT * i) + GRID_SECTOR_HEIGHT);
			vec_2x recRightBottom((GRID_SECTOR_WIDTH * j) + GRID_SECTOR_WIDTH, GRID_SECTOR_HEIGHT * i);

			m_gridRect[i][j] = std::make_pair(std::unique_ptr<GameObject>(GameObjectFactory::GetInstance()->CreateGameRectangle(recLeftTop, recRightBottom, color)), false);
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

	vector::vector_4x::SetVector(lineColor, 0.0f, 0.5f, 0.5f, 0.3f);
	GameObject* gameLine = nullptr;

	// Horizontal lines
	for (int gridHeightIndex = 0; gridHeightIndex < WORLD_GRID_HEIGHT_COUNT; ++gridHeightIndex)
	{
		vector::vector_2x::SetVector(startPoint, 0.0f, GRID_SECTOR_HEIGHT * gridHeightIndex);
		vector::vector_2x::SetVector(endPoint, GRID_SECTOR_WIDTH * WORLD_GRID_WIDTH_COUNT, GRID_SECTOR_HEIGHT * gridHeightIndex);

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);
		sceneGridLines.push_back(std::unique_ptr<GameObject>(gameLine));
	}

	// Vertical lines
	for (int gridWidthIndex = 0; gridWidthIndex < WORLD_GRID_WIDTH_COUNT; ++gridWidthIndex)
	{
		vector::vector_2x::SetVector(startPoint, GRID_SECTOR_WIDTH * gridWidthIndex, 0.0f);
		vector::vector_2x::SetVector(endPoint, GRID_SECTOR_WIDTH * gridWidthIndex, GRID_SECTOR_HEIGHT * WORLD_GRID_HEIGHT_COUNT);

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 5, lineColor);
		sceneGridLines.push_back(std::unique_ptr<GameObject>(gameLine));
	}
}

void Level::RemoveVisibleGridLines()
{
	sceneGridLines.clear();
}

void Level::RenderSectorDebugColor()
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
	std::unique_ptr<LevelPackage> levelData((LevelPackage*)LevelLoader::GetInstance()->Load(working_dir_path + "/assets/levels/" + LEVEL_1));

	// Create the entities for this level
	ConstructLevel(levelData.get());
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

	for (int index = 0; index < sceneObjectsCollection.Count(); ++index)
	{
		//TODO - implement on the FastAccessCollection a rearange feature so that most of the occupied slots are grouped in front of the array
		if (sceneObjectsCollection.IsSlotFree(index))
			continue;

		if (!sceneObjectsCollection.Retrive(index)->IsAlive())
		{
			RemoveObject(index);
			continue;
		}
		GameObject* currSceneObj = sceneObjectsCollection.Retrive(index);

		currSceneObj->Update();
		if (currSceneObj->IsFlagON(OBJECT_IS_MOVING))
		{
			isMovementInCurrUpdate = true;
#if(DEBUG_SECTION)
			//TODO - could this code be executed outside the for?
			if (!isAlreadyReset)
			{
				// Reset the color on all sector objects to green
				isAlreadyReset = true;
				for (unsigned int i = 0; i < WORLD_GRID_HEIGHT_COUNT; ++i)
					for (unsigned int j = 0; j < WORLD_GRID_WIDTH_COUNT; ++j)
					{
						((GameRectangle*)(m_gridRect[i][j].first.get()))->SetColor(green);
					}
			}
#endif
			// Get the old area values and remove the object pointer from each sector
			std::array<int, 4> oldGridMapping = currSceneObj->GetOccupiedGriDArea();

			// Check if the old occupied grid area is not out of bounce
			if (!IsAreaOutOfBounce(oldGridMapping[0], oldGridMapping[1], oldGridMapping[2], oldGridMapping[3]))
			{
				for (int yAxisIndex = oldGridMapping[0]; yAxisIndex >= oldGridMapping[2]; yAxisIndex--)
					for (int xAxisIndex = oldGridMapping[1]; xAxisIndex <= oldGridMapping[3]; xAxisIndex++)
					{
						Sector* oldSector = GetSectorAtIndex(xAxisIndex, yAxisIndex);
						oldSector->RemoveCollidingObject(currSceneObj->GetID()); //TODO pt consistenta, aceasta metoda trebuie sa ia tot un Object
#if(DEBUG_SECTION)
						if (!oldSector->HasCollidingObjects())
						{
							// Deactivate the visibility on the old area
							SetGridRectVisibility(xAxisIndex, yAxisIndex, false);
						}
#endif
					}
			} 

			// Remove the old colliding neighbours
			currSceneObj->ClearCollidingNeighbours();

			// Get the rectangle of the game object and calculate the occupied area in the grid
			Rectangle objRect = currSceneObj->GetObjectWorldRect();
			ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

			// Check if the new occupied grid area is not out of bounce
			if (!IsAreaOutOfBounce(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex))
			{
				// Add the game object pointer to the new sectors and construct new colliding neighbours
				currSceneObj->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

				for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
					for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
					{
						Sector* newSector = GetSectorAtIndex(xAxisIndex, yAxisIndex);
						const std::map<int, GameObject*> collidingObj = newSector->GetCollidingObjects();
						std::map<int, GameObject*>::const_iterator ite = collidingObj.begin();
						for (; ite != collidingObj.end(); ite++)
						{
							currSceneObj->AddCollidingNeighbour(ite->second);
							ite->second->AddCollidingNeighbour(currSceneObj);
						}

						newSector->AddCollidingObject(currSceneObj);
#if(DEBUG_SECTION)
						// Activate the visibility on the new area
						SetGridRectVisibility(xAxisIndex, yAxisIndex, true);
#endif
					}
			}

			// Check if object is colliding with other objects from scene
			const std::map<const int, GameObject*> collidingNeighbours = currSceneObj->GetCollidingNeighbours();
			std::map<const int, GameObject*>::const_iterator ite = collidingNeighbours.begin();
			for (; ite != collidingNeighbours.end(); ite++)
			{
				//TODO we should use a general collision detection here that implements something like CollisionDetectionAABB
				//TODO dependency injection
				bool isColliding = Physics2D::CollisionDetectionAABB(objRect, ite->second->GetObjectWorldRect());
				if (isColliding)
				{
#if(DEBUG_SECTION)
					// Color in red the sectors occupied by the objects that are colliding 
					vec_4x color;
					vector::vector_4x::SetVector(color, 1.0f, 0.0f, 0.0f, 1.0f);

 					std::array<int, 4> objectAGridMapping = currSceneObj->GetOccupiedGriDArea();
					std::array<int, 4> objectBGridMapping = ite->second->GetOccupiedGriDArea();

					for (int yAxisIndex = objectAGridMapping[0]; yAxisIndex >= objectAGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectAGridMapping[1]; xAxisIndex <= objectAGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first.get()))->SetColor(color);
						}

					for (int yAxisIndex = objectBGridMapping[0]; yAxisIndex >= objectBGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectBGridMapping[1]; xAxisIndex <= objectBGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first.get()))->SetColor(color);
						}

						//std::cout << "Collision between <" << currSceneObj->GetID() << "> and <" << ite->second->GetID() << ">" << std::endl;
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
			const std::map<const int, GameObject*> collidingNeighbours = currSceneObj->GetCollidingNeighbours();
			std::map<const int, GameObject*>::const_iterator ite = collidingNeighbours.begin();
			for (; ite != collidingNeighbours.end(); ite++)
			{
				Rectangle objRect = currSceneObj->GetObjectWorldRect();
				bool isColliding = Physics2D::CollisionDetectionAABB(objRect, ite->second->GetObjectWorldRect());
				if (isColliding)
				{
					// Color in red the sectors occupied by the objects that are colliding
					vec_4x color;
					vector::vector_4x::SetVector(color, 1.0f, 0.0f, 0.0f, 1.0f);

					std::array<int, 4> objectAGridMapping = currSceneObj->GetOccupiedGriDArea();
					std::array<int, 4> objectBGridMapping = ite->second->GetOccupiedGriDArea();

					for (int yAxisIndex = objectAGridMapping[0]; yAxisIndex >= objectAGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectAGridMapping[1]; xAxisIndex <= objectAGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first.get()))->SetColor(color);
						}

					for (int yAxisIndex = objectBGridMapping[0]; yAxisIndex >= objectBGridMapping[2]; yAxisIndex--)
						for (int xAxisIndex = objectBGridMapping[1]; xAxisIndex <= objectBGridMapping[3]; xAxisIndex++)
						{
							((GameRectangle*)(m_gridRect[yAxisIndex][xAxisIndex].first.get()))->SetColor(color);
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

	// Update the grid lines
#if(DEBUG_SECTION)
	for (auto& ite : sceneGridLines)
	{
		ite->Update();
	}
#endif
}

void Level::PreDraw()
{
	sceneRenderingObjects.clear();

	for (int index = 0; index < sceneObjectsCollection.Count(); ++index)
	{
		if (!sceneObjectsCollection.IsSlotFree(index))
			sceneRenderingObjects.insert(std::pair<float, int>(sceneObjectsCollection.Retrive(index)->GetZBuffer(), index));
	}
}

void Level::Draw()
{
	// Clear the color buffer
	Painter::ClearScreen();

#if(DEBUG_SECTION)
	if(isSectorColorRenderEnabled)
		RenderSectorDebugColor();
#endif

	// Draw all the level entities
	for (auto ite = sceneRenderingObjects.begin(); ite != sceneRenderingObjects.end(); ++ite)
	{
		sceneObjectsCollection.Retrive(ite->second)->PreDraw();
		sceneObjectsCollection.Retrive(ite->second)->Draw();
	}

#if(DEBUG_SECTION)
	for (const auto& line : sceneGridLines)
	{
		line->PreDraw();
		line->Draw();
	}
#endif
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
			else if (wrapper->action == Actions::Debug::DEBUG_OBJECT_SECTOR_MAPPING)
			{
				isSectorColorRenderEnabled = !isSectorColorRenderEnabled;
			}
			else if (wrapper->action == Actions::Debug::DEBUG_OBJECT_RECTANGLE)
			{
				isOutlineEnabled = !isOutlineEnabled;

				// All the renderable objects in the scene must get the new value
				for (int index = 0; index < sceneObjectsCollection.Count(); ++index)
				{
					if (!sceneObjectsCollection.IsSlotFree(index) &&
						sceneObjectsCollection.Retrive(index)->IsAlive() &&
						sceneObjectsCollection.Retrive(index)->IsFlagON(OBJECT_IS_RENDERABLE))
					{
						sceneObjectsCollection.Retrive(index)->SetOutline(isOutlineEnabled);
					}
				}
			}
#endif
		}
	}
}

Sector* Level::GetSectorAtIndex(unsigned int x, unsigned int y)
{
	return (x < m_gameWorldGrid.size() && y < m_gameWorldGrid[x].size()) ? m_gameWorldGrid[x][y].get() : nullptr;
}

void Level::ComputeObjectToGridMapping(const Rectangle& objectRect, int& outTopIndex, int& outLeftIndex, int& outBottomIndex, int& outRightIndex)
{
	static float gridSectorWidthFloat = (float)GRID_SECTOR_WIDTH;
	static float gridSectorHeightFloat = (float)GRID_SECTOR_HEIGHT;

	// Part 1: For every top, bottom, left and right we calculate the index
	float tempObjectTopGridIndex = objectRect.GetTop() / gridSectorHeightFloat;
	float tempObjectBottomGridIndex = objectRect.GetBottom() / gridSectorHeightFloat;
	float tempObjectLeftGridIndex = objectRect.GetLeft() / gridSectorWidthFloat;
	float tempObjectRightGridIndex = objectRect.GetRight() / gridSectorWidthFloat;

	// Part 2: We add +1 for top and left
	outTopIndex = (int)tempObjectTopGridIndex;
	outLeftIndex = (int)tempObjectLeftGridIndex;
	outBottomIndex = (int)tempObjectBottomGridIndex;
	outRightIndex = (int)tempObjectRightGridIndex;

	// Part 3: We add +1 for top and right only if modulo of multiplier if non-zero
	if (std::fmod(objectRect.GetTop(), gridSectorHeightFloat) == 0.0f)
		--outTopIndex;

	if (std::fmod(objectRect.GetRight(), gridSectorWidthFloat) == 0.0f)
		--outRightIndex;
}

bool Level::IsAreaOutOfBounce(const float outTopIndex, const float outLeftIndex, const float outBottomIndex, const float outRightIndex)
{
	return (outTopIndex < 0 || outTopIndex >= WORLD_GRID_HEIGHT_COUNT) ||
		   (outBottomIndex < 0 || outBottomIndex >= WORLD_GRID_HEIGHT_COUNT) ||
		   (outLeftIndex < 0 || outLeftIndex >= WORLD_GRID_WIDTH_COUNT) ||
		   (outRightIndex < 0 || outRightIndex >= WORLD_GRID_WIDTH_COUNT);
}

void Level::RemoveObject(int index)
{
	GameObject* todelGameObject = sceneObjectsCollection.Retrive(index);
	sceneRenderingObjects.erase(todelGameObject->GetZBuffer());
	sceneObjectsCollection.Free(index);
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

	return m_gridRect[y][x].first.get();
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