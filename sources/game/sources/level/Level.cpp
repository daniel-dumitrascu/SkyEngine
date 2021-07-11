#include "Level.h"
#include "geometry/mesh/MeshLoader.h"
#include "geometry/mesh/MeshResources.h"
#include "texture/TextureLoader.h"
#include "texture/TextureResources.h"
#include "shaders/ShaderLoader.h"
#include "shaders/ShaderResources.h"
#include "animation/AnimDataResources.h"
#include "animation/AnimDataLoader.h"
#include "level/LevelLoader.h"
#include "level/LevelData.h"
#include "LevelDefines.h"
#include "global/GlobalPaths.h"
#include "video/Painter.h"
#include "global/GlobalData.h"
#include "../game_objects/GameObjectFactory.h"
#include "utils/Physics2D.h"
#include "../defines/ResourceDefines.h"
#include "platform/input/InputManager.h"
#include "input/InputHandleProfiles.h"
#include "bindings/BindingsManager.h"

#include <math.h>
#include <array>


#if(DEBUG_SECTION)
#include "primitive/Line.h"
#include "primitive/Rectangle.h"
#include "primitive/GameRectangle.h"
#include "primitive/GameLine.h"
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
	// Remove all the entities from the level 
	for (int index = 0; index < m_sceneObjects.Count(); ++index)
	{
		if(!m_sceneObjects.IsSlotFree(index))
			RemoveObject(index);
	}
		
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


	/* Reset score and other settings */
	//TODO to do
}

void Level::ConstructLevel(LevelPackage* levelData)
{
	GameObject* obj;
	int outTopIndex = 0;
	int outLeftIndex = 0;
	int outBottomIndex = 0;
	int outRightIndex = 0;

	InputManager* input_manager = InputManager::GetInstance();
	
	for (std::list<GameObjectPackage>::iterator ite = levelData->m_level_data.begin(); ite != levelData->m_level_data.end(); ++ite)
	{
		obj = GameObjectFactory::GetInstance()->CreateGameObject((*ite));
		if (obj)
		{
			// Calculation  of the object in tile map
			Rectangle objRect = obj->GetObjectWorldRect();
			ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);
			obj->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

			// Add the object in every tile with which it intersects
			for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
				for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
				{
					Tile* newTile = GetGridTile(xAxisIndex, yAxisIndex);
					newTile->AddCollidingObject(obj);
#if(DEBUG_SECTION)
					// Activate the visibility on the new area
					SetGridRectVisibility(xAxisIndex, yAxisIndex, true);
					GetGridRectObject(xAxisIndex, yAxisIndex)->Update();
#endif
				}

			//TODO for a quick access of the game object in the main storage collection, I need to store in it (in the object)
			//the index returned from "Add" method. 
			//Otherwise, it will be very difficult to delete it. So, the index will also be stored in the object.
			//It's the best way, ensuring us a speed in accessing and deleting.
			//TODO Test all the cases because there might be problems with the returned index. This is not always returned as it should
			/*TODO ??? index = */m_sceneObjects.Occupy(obj);

			if(obj->IsFlagON(OBJECT_IS_CONTROLLABLE))
			{			
				int subId = input_manager->AddSubscriber((Controllable*)obj);
				if(subId == -1)
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
}

void Level::ConstructGameGrid()
{
#if(DEBUG_SECTION)
	vec_4x color;
	vector::vector_4x::SetVector(color, 0.0f, 1.0f, 0.0f, 1.0f);
#endif

	// Resize the row count of the grid
	m_gameWorldGrid.resize(WORLD_GRID_ROW_COUNT);
#if(DEBUG_SECTION)
	m_gridRect.resize(WORLD_GRID_ROW_COUNT);
#endif

	// Create a generic rectangle in [-1, 1] coordonate space
	vec_2x leftTop(-50.0f, 50.0f);
	vec_2x rightBottom(50.0f, -50.0f);
	Rectangle genericRect(leftTop, rightBottom);

	for (unsigned int i = 0; i < WORLD_GRID_ROW_COUNT; ++i)
	{
		// Resize each row by the number of column
		m_gameWorldGrid[i].resize(WORLD_GRID_COLUMN_COUNT);
#if(DEBUG_SECTION)
		m_gridRect[i].resize(WORLD_GRID_COLUMN_COUNT);
#endif

		// Iterate in the new allocated row and create new tiles
		for (unsigned int j = 0; j < WORLD_GRID_COLUMN_COUNT; ++j)
		{
			m_gameWorldGrid[i][j] = new Tile(i, j, genericRect);

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

	vector::vector_4x::SetVector(lineColor, 0.0f, 1.0f, 0.0f, 1.0f);
	GameObject* gameLine = nullptr;

	// Horizontal lines
	for (int gridHeightIndex = 0; gridHeightIndex < m_gridRect.size(); ++gridHeightIndex)
	{
		const Rectangle firstRect = m_gridRect[gridHeightIndex][0].first->GetObjectWorldRect();
		const Rectangle lastRect = m_gridRect[gridHeightIndex][m_gridRect[gridHeightIndex].size() - 1].first->GetObjectWorldRect();

		vector::vector_2x::SetVector(startPoint, firstRect.GetLeft(), firstRect.GetTop());
		vector::vector_2x::SetVector(endPoint, lastRect.GetRight(), lastRect.GetTop());

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);
		m_gridLinesIds.push_back(m_sceneObjects.Occupy(gameLine));
	}

	// Vertical lines
	for (int gridWidthIndex = 0; gridWidthIndex < m_gridRect[0].size(); ++gridWidthIndex)
	{
		const Rectangle firstRect = m_gridRect[0][gridWidthIndex].first->GetObjectWorldRect();
		const Rectangle lastRect = m_gridRect[m_gridRect.size() - 1][gridWidthIndex].first->GetObjectWorldRect();

		vector::vector_2x::SetVector(startPoint, firstRect.GetLeft(), firstRect.GetBottom());
		vector::vector_2x::SetVector(endPoint, lastRect.GetLeft(), lastRect.GetTop());

		gameLine = GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);
		m_gridLinesIds.push_back(m_sceneObjects.Occupy(gameLine));
	}
}

void Level::RemoveVisibleGridLines()
{
	for (int i=0; i < m_gridLinesIds.size(); ++i)
	{
		delete m_sceneObjects.Free(m_gridLinesIds[i]);
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

	ConstructGameGrid();

#if(DEBUG_SECTION)
	if(isGridDrawingEnabled)
		AddVisibleGridLines();
#endif

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

	GameObject* currObject = nullptr;

	for (int index = 0; index < m_sceneObjects.Count(); ++index)
	{
		if(!m_sceneObjects.IsSlotFree(index))
		{
			if(!m_sceneObjects.Retrive(index)->IsAlive())
			{
				RemoveObject(index);
				continue;
			}

			currObject = m_sceneObjects.Retrive(index);
			currObject->Update();

			if (currObject->IsFlagON(OBJECT_IS_MOVING))
			{
				//currObject->SetFlagOFF(OBJECT_IS_MOVING); 
				//TODO - Am inlaturat acest SetFlagOFF(OBJECT_IS_MOVING) deoarece acum pe player iau decizia daca obiectul se misca sau nu in update.
				//Iar aici doar verific daca obiectul se misca sau nu. Vezi cum poti face si cu celelalte obiecte.
																

#if(DEBUG_SECTION)
				if (!isAlreadyReset)
				{
					// Reset the color on all tile objects to green
					isAlreadyReset = true;
					vec_4x green;
					vector::vector_4x::SetVector(green, 0.0f, 1.0f, 0.0f, 1.0f);
					for (unsigned int i = 0; i < WORLD_GRID_ROW_COUNT; ++i)
						for (unsigned int j = 0; j < WORLD_GRID_COLUMN_COUNT; ++j)
						{
							((GameRectangle*)(m_gridRect[i][j].first))->SetColor(green);
						}
				}		
#endif

				// Get the rectangle of the game object and calculate the occupied area in the grid
				Rectangle objRect = currObject->GetObjectWorldRect();
				ComputeObjectToGridMapping(objRect, outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

				// Get the old area values and remove the object pointer from each tile
				std::array<int, 4> oldGridMapping = currObject->GetOccupiedGriDArea();

				for (int yAxisIndex = oldGridMapping[0]; yAxisIndex >= oldGridMapping[2]; yAxisIndex--)
					for (int xAxisIndex = oldGridMapping[1]; xAxisIndex <= oldGridMapping[3]; xAxisIndex++)
					{
						Tile* oldTile = GetGridTile(xAxisIndex, yAxisIndex);
						std::string label = currObject->GetLabel().GetStrLabel();
						oldTile->RemoveCollidingObject(label); //TODO pt consistenta, aceasta metoda trebuie sa ia tot un Object
#if(DEBUG_SECTION)
						if (!oldTile->HasCollidingObjects())
						{
							// Deactivate the visibility on the old area
							SetGridRectVisibility(xAxisIndex, yAxisIndex, false);
						}
#endif
					}

				// Remove the old colliding neighbours
				currObject->ClearCollidingNeighbours();

				// Add the game object pointer to the new tiles and construct new colliding neighbours
				currObject->SetOccupiedGridArea(outTopIndex, outLeftIndex, outBottomIndex, outRightIndex);

				for (int yAxisIndex = outTopIndex; yAxisIndex >= outBottomIndex; yAxisIndex--)
					for (int xAxisIndex = outLeftIndex; xAxisIndex <= outRightIndex; xAxisIndex++)
					{
						Tile* newTile = GetGridTile(xAxisIndex, yAxisIndex);

						const std::map<std::string, GameObject*> collidingObj = newTile->GetCollidingObjects();
						std::map<std::string, GameObject*>::const_iterator ite = collidingObj.begin();
						for (; ite != collidingObj.end(); ite++)
						{
							currObject->AddCollidingNeighbour(ite->second);
							ite->second->AddCollidingNeighbour(currObject);
						}

						newTile->AddCollidingObject(currObject);
#if(DEBUG_SECTION)
						// Activate the visibility on the new area
						SetGridRectVisibility(xAxisIndex, yAxisIndex, true);
						GetGridRectObject(xAxisIndex, yAxisIndex)->Update();
#endif
					}

				// Check if object is colliding with other objects from scene
				const std::map<const std::string, GameObject*> collidingNeighbours = currObject->GetCollidingNeighbours();
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

						std::array<int, 4> objectAGridMapping = currObject->GetOccupiedGriDArea();
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

						//std::cout << "Coliziune intre <" << currObject->GetLabel().GetStrLabel() << "> si <" << ite->second->GetLabel().GetStrLabel() << ">" << std::endl;
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
				const std::map<const std::string, GameObject*> collidingNeighbours = currObject->GetCollidingNeighbours();
				std::map<const std::string, GameObject*>::const_iterator ite = collidingNeighbours.begin();
				for (; ite != collidingNeighbours.end(); ite++)
				{
					Rectangle objRect = currObject->GetObjectWorldRect();
					bool isColliding = Physics2D::CollisionDetectionAABB(objRect, ite->second->GetObjectWorldRect());
					if (isColliding)
					{
						// Color in red the tiles occupied by the objects that are colliding 
						vec_4x color;
						vector::vector_4x::SetVector(color, 1.0f, 0.0f, 0.0f, 1.0f);

						std::array<int, 4> objectAGridMapping = currObject->GetOccupiedGriDArea();
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
	for (int index = 0; index < m_sceneObjects.Count(); ++index)
	{
		if (!m_sceneObjects.IsSlotFree(index))
		{
			m_sceneObjects.Retrive(index)->PreDraw();
			m_sceneObjects.Retrive(index)->Draw();
		}
	}
}

void Level::InputActionNotify(const InputEventBatch& inputBatch)
{
	int const batchSize = inputBatch.getDataBatchSize();
	if(batchSize > 0)
	{
		for(int i=0; i < batchSize; ++i)
		{
			int action = inputToActionBindings->GetBinding(
					inputBatch.getDataAtIndex(i).button);
			if(action == -1)
				continue;

			if (action == Actions::Game::GAME_EXIT)
			{
				exit(0); //TODO here should be a new state for closing
				break;
			} 
#if(DEBUG_SECTION)
			else if (action == Actions::Debug::DEBUG_GRID_DRAW)
			{
				isGridDrawingEnabled = !isGridDrawingEnabled;
				if (isGridDrawingEnabled)
					AddVisibleGridLines();
				else
					RemoveVisibleGridLines();
			}
			else if (action == Actions::Debug::DEBUG_OBJECT_TILE_MAPPING)
			{
				isColorTileRenderEnabled = !isColorTileRenderEnabled;
			}
			else if (action == Actions::Debug::DEBUG_OBJECT_RECTANGLE)
			{
				isOutlineEnabled = !isOutlineEnabled;

				// All the renderable objects in the scene must get the new value
				for (int index = 0; index < m_sceneObjects.Count(); ++index)
				{
					if (!m_sceneObjects.IsSlotFree(index))
					{
						GameObject* obj = m_sceneObjects.Retrive(index);
						if(obj->IsAlive() && obj->IsFlagON(OBJECT_IS_RENDERABLE))
							obj->SetOutline(isOutlineEnabled);
					}
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
	static float virtualWorldMultiplierFloat = (float)VIRTUAL_WORLD_MULTIPLIER;

	// Part 1: For every top, bottom, left and right we calculate the index
	float tempObjectTopGridIndex = objectRect.GetTop() / virtualWorldMultiplierFloat;
	float tempObjectBottomGridIndex = objectRect.GetBottom() / virtualWorldMultiplierFloat;
	float tempObjectLeftGridIndex = objectRect.GetLeft() / virtualWorldMultiplierFloat;
	float tempObjectRightGridIndex = objectRect.GetRight() / virtualWorldMultiplierFloat;

	// Part 2: We add +1 for top and left
	outTopIndex = (int)tempObjectTopGridIndex;
	outLeftIndex = (int)tempObjectLeftGridIndex;
	outBottomIndex = (int)tempObjectBottomGridIndex;
	outRightIndex = (int)tempObjectRightGridIndex;

	// Part 3: We add +1 for top and right only if modulo of multiplier if non-zero
	if (std::fmod(objectRect.GetTop(), virtualWorldMultiplierFloat) == 0.0f)
		--outTopIndex;

	if (std::fmod(objectRect.GetRight(), virtualWorldMultiplierFloat) == 0.0f)
		--outRightIndex;
}

Tile* Level::GetGridTile(int x, int y)
{
	// y - row
	// x - column

	if (y >= m_gameWorldGrid.size())
		return nullptr;

	if (x >= m_gameWorldGrid[y].size())
		return nullptr;

	return m_gameWorldGrid[y][x];
}

void Level::RemoveObject(int index)
{
	GameObject* todelGameObject = m_sceneObjects.Retrive(index);
	delete todelGameObject;
	m_sceneObjects.Free(index);
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