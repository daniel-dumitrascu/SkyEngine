#include "Player.h"
#include "video/Painter.h"
#include "global/GlobalData.h"
#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include "GameObjectDefines.h"
#include "../states/GameStateManager.h"
#include "../states/GameStateMainMenu.h"
#include "platform/input/InputManager.h"
#include "utils/Motion.h"

#if(DEBUG_SECTION)
#include "GameObjectFactory.h"
#endif

Player::Player(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, GameObjectLabel& gameLabel) :
	GameObject(mesh, texture, shader, postX, postY, scale, gameLabel, INPUT_HANDLE_PROFILE_GAMEOBJECT), hasObjectMovedThisFrame(false),
	speedGoal(PLAYER_SPEED_GOAL), currentSpeed(1.0f)
{
	// Set a default direction
	vector::vector_3x::SetVector(currDirection, 0.0f, 0.0f, 0.0f);
	vector::vector_3x::SetVector(newDirection, 0.0f, 0.0f, 0.0f);

	vector::vector_3x::SetVector(lastFramePos, m_world_position);

	m_action_handler[Actions::Gameplay::GAMEPLAY_UNDEFINED]  = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_UP]	 = &Player::OnMoveUp;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_DOWN]	 = &Player::OnMoveDown;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_LEFT]	 = &Player::OnMoveLeft;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_RIGHT] = &Player::OnMoveRight;
	m_action_handler[Actions::Gameplay::GAMEPLAY_ATTACK]	 = nullptr;

	Init();
}

Player::~Player()
{
	Painter::RemoveGeometryFromGPU(m_wireframe);
	m_wireframe = nullptr;
	m_texture = nullptr;

#if(DEBUG_SECTION)
	delete leftOutline;
	delete rightOutline;
	delete topOutline;
	delete bottomOutline;
#endif
}

void Player::Init()
{
	Painter::SendGeometryToGPU(m_wireframe);

	/* Reset m_wp matrix */
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	/* Construct a world-projection matrix */
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);

#if(DEBUG_SECTION)
	vec_4x lineColor;
	vec_2x startPoint;
	vec_2x endPoint;
	vector::vector_4x::SetVector(lineColor, 0.0f, 0.0f, 1.0f, 1.0f);
	Rectangle rect = GetObjectWorldRect();

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetLeft(), rect.GetBottom());
	leftOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetRight(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetBottom());
	rightOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetTop());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetTop());
	topOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);

	vector::vector_2x::SetVector(startPoint, rect.GetLeft(), rect.GetBottom());
	vector::vector_2x::SetVector(endPoint, rect.GetRight(), rect.GetBottom());
	bottomOutline = (GameLine*)GameObjectFactory::GetInstance()->CreateGameLine(startPoint, endPoint, 3, lineColor);
#endif
}

void Player::PreDraw()
{
	//TODO function calls that must be executed in the init step
	/***********************************************************************************************************************/
	// move them in DrawScheme
	// for every shader pair :)
	// I call them once in init and then send the info as mesh_id and tex_id to every object in the scene

	//TODO call them each time I need to draw objects 
	//the functions will be called to every object group from the scenne that is assigned to a shader pair
	Painter::GetInstance()->SelectShader(m_shader);
	Painter::SetActiveTexture(m_shader, "s_texture");
	/***********************************************************************************************************************/

	/* Selecting the texture */
	Painter::SetBindTexture(m_texture->bind_id);

	/* Select data buffers */
	Painter::SelectArrayBuffer(m_wireframe->GetVBOVert());
	Painter::SetStartDrawData(Painter::GetInstance()->GetMeshLocation(), sizeof(Vertex), 0);

	Painter::SelectIndxBuffer(m_wireframe->GetVBOIndx());
	Painter::SetStartDrawData(Painter::GetInstance()->GetTexLocation(), sizeof(Vertex), sizeof(vec_2x));

	/* Set matrix drawing data */
	Painter::SetDrawMatrix4Data(Painter::GetInstance()->GetMemoryLocation(), (const float*)&(m_wp_matrix.elem[0]));
}

void Player::Draw()
{
	// Draw the actual data
	Painter::DrawData(m_wireframe->GetGeometryCount());

	// We are going to draw here the debug rect if that's enabled
#if(DEBUG_SECTION)
	if (isOutlineEnabled)
	{
		leftOutline->PreDraw();
		leftOutline->Draw();

		rightOutline->PreDraw();
		rightOutline->Draw();

		topOutline->PreDraw();
		topOutline->Draw();

		bottomOutline->PreDraw();
		bottomOutline->Draw();
	}
#endif
}

void Player::Update()
{
	UpdateMovement();

	// Set the new position of the object in game world
	matrix::game_matrix::SetWorldPosition(m_world_matrix, m_world_position);

	// Make the decision if the object is still moving or not
	if (m_world_position != lastFramePos)
		lastFramePos = m_world_position;
	else
		SetFlagOFF(OBJECT_IS_MOVING);

	// Reset m_wp matrix 
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	// Construct a world-projection matrix 
	matrix::game_matrix::WorldProjMatrix(m_wp_matrix, m_world_matrix, proj_matrix);

#if(DEBUG_SECTION)
	if (isOutlineEnabled)
	{
		vec_2x newStartPoint;
		vec_2x newEndPoint;
		Rectangle rect = GetObjectWorldRect();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetLeft(), rect.GetBottom());
		leftOutline->UpdateStartAndEnd(newStartPoint, newEndPoint);
		leftOutline->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetRight(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		rightOutline->UpdateStartAndEnd(newStartPoint, newEndPoint);
		rightOutline->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetTop());
		topOutline->UpdateStartAndEnd(newStartPoint, newEndPoint);
		topOutline->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetBottom());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		bottomOutline->UpdateStartAndEnd(newStartPoint, newEndPoint);
		bottomOutline->Update();
	}
#endif
}

void Player::InputActionNotify(const InputEventBatch& inputBatch)
{
	hasObjectMovedThisFrame = false;
	int const batchSize = inputBatch.getDataBatchSize();
	if(batchSize > 0)
	{
		for(int i=0; i < batchSize; ++i)
		{
			int action = inputToActionBindings->GetBinding(inputBatch.getDataAtIndex(i));
			if (action == -1)
				continue;

			if (inputBatch.getDataAtIndex(i).status == KEYBOARD_BUTTON_PRESS)
			{
				if (action == Actions::Game::GAME_EXIT)
				{
					GameStateManager::PushState(new GameStateMainMenu);
					// Once we got the exit action we don't need to
					// check for the other actions
					break;
				}
				else if (action < Actions::Gameplay::GAMEPLAY_COUNT && m_action_handler[action])
				{
					void (Player::*handle_event)() = m_action_handler[action];
					if (handle_event)
						(this->*(handle_event))();
				}
			}
			else if(inputBatch.getDataAtIndex(i).status == KEYBOARD_BUTTON_RELEASE)
			{
				if (action == Actions::Gameplay::GAMEPLAY_MOVE_DOWN || action == Actions::Gameplay::GAMEPLAY_MOVE_UP ||
					action == Actions::Gameplay::GAMEPLAY_MOVE_LEFT || action == Actions::Gameplay::GAMEPLAY_MOVE_RIGHT)
				{
					speedGoal = 0.0f;
				}
			}
		}

		if (hasObjectMovedThisFrame)
		{	
			// At this point I know that the object has moved so I need to make 
			// the necessary adjustments like using the new computed direction vector
			vector::vector_3x::Normalization(newDirection, newDirection);
			currDirection = newDirection;
			vector::vector_3x::SetVector(newDirection, 0.0f, 0.0f, 0.0f);
		}
	}
}

void Player::OnMoveUp()
{
	speedGoal = PLAYER_SPEED_GOAL;
	hasObjectMovedThisFrame = true;

	ComputeDirection(0.0f, 1.0f, 0.0f);
	SetFlagON(OBJECT_IS_MOVING);
}

void Player::OnMoveDown()
{
	speedGoal = PLAYER_SPEED_GOAL;
	hasObjectMovedThisFrame = true;

	ComputeDirection(0.0f, -1.0f, 0.0f);
	SetFlagON(OBJECT_IS_MOVING);
}

void Player::OnMoveLeft()
{
	speedGoal = PLAYER_SPEED_GOAL;
	hasObjectMovedThisFrame = true;

	ComputeDirection(-1.0f, 0.0f, 0.0f);
	SetFlagON(OBJECT_IS_MOVING);
}

void Player::OnMoveRight()
{
	speedGoal = PLAYER_SPEED_GOAL;
	hasObjectMovedThisFrame = true;

	ComputeDirection(1.0f, 0.0f, 0.0f);
	SetFlagON(OBJECT_IS_MOVING);
}

void Player::ComputeDirection(float x, float y, float z)
{
	vec_3x dir(x, y, z);
	vector::vector_3x::Addition(newDirection, newDirection, dir);
}

void Player::UpdateMovement()
{
	vec_3x directionAndSpeed;
	currentSpeed = Motion::MotionInterpolation(speedGoal, currentSpeed, 0.15f * DELTA_TIME_BOOST);
	vector::vector_3x::DotProduct(directionAndSpeed, currDirection, currentSpeed * 0.15f);
	vector::vector_3x::Addition(m_world_position, m_world_position, directionAndSpeed);
}
