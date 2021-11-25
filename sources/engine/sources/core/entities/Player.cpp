#include "Player.h"
#include "video/Painter.h"
#include "global/GlobalData.h"
#include "texture/Texture.h"
#include "utils/Motion.h"
#include "states/GameStateManager.h"
#include "states/GameStateMainMenu.h"
#include "level/Level.h"


Player::Player(WireFrame* mesh, Texture* texture, int shader, const float postX, const float postY, int scale, int zBuffer) :
	GameObject(mesh, texture, shader, postX, postY, scale, INPUT_HANDLE_PROFILE_GAMEOBJECT), hasObjectMovedThisFrame(false),
	speedGoal(0.0f), currentSpeed(0.0f)
{
	m_zbuffer = zBuffer;

	// Set a default direction
	vector::vector_3x::SetVector(currDirection, 0.0f, 0.0f, 0.0f);
	vector::vector_3x::SetVector(newDirection, 0.0f, 0.0f, 0.0f);

	vector::vector_3x::SetVector(lastFramePos, m_world_position);

	m_action_handler[Actions::Gameplay::GAMEPLAY_UNDEFINED]  = nullptr;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_UP]	 = &Player::OnMovement;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_DOWN]	 = &Player::OnMovement;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_LEFT]	 = &Player::OnMovement;
	m_action_handler[Actions::Gameplay::GAMEPLAY_MOVE_RIGHT] = &Player::OnMovement;
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

	/* Construct a world-view-projection matrix */
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);
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
	float framesElapsedTime = global_timer.GetElapsed();

	// Keep this value from growing too large
	if (framesElapsedTime > 0.15f)
		framesElapsedTime = 0.15f;

	UpdateMovement(framesElapsedTime);

	// Set the new position of the object in game world
	matrix::game_matrix::SetWorldPosition(m_world_matrix, m_world_position);

	// Make the decision if the object is still moving or not
	if (m_world_position != lastFramePos)
		lastFramePos = m_world_position;
	else
		SetFlagOFF(OBJECT_IS_MOVING);

	// Reset m_wp matrix 
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	// Construct a world-view-projection matrix
	const mat_4x viewMatrix = Level::GetInstance()->GetActiveCamera()->GetViewMatrix();
	matrix::game_matrix::BuildWorldViewProjMatrix(m_wp_matrix, m_world_matrix, viewMatrix, proj_matrix);

#if(DEBUG_SECTION)
	if (isOutlineEnabled)
	{
		vec_2x newStartPoint;
		vec_2x newEndPoint;
		Rectangle rect = GetObjectWorldRect();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetLeft(), rect.GetBottom());
		GameLine* left = static_cast<GameLine*>(leftOutline);
		left->SetPosition(newStartPoint, newEndPoint);
		left->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetRight(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		GameLine* right = static_cast<GameLine*>(rightOutline);
		right->SetPosition(newStartPoint, newEndPoint);
		right->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetTop());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetTop());
		GameLine* top = static_cast<GameLine*>(topOutline);
		top->SetPosition(newStartPoint, newEndPoint);
		top->Update();

		vector::vector_2x::SetVector(newStartPoint, rect.GetLeft(), rect.GetBottom());
		vector::vector_2x::SetVector(newEndPoint, rect.GetRight(), rect.GetBottom());
		GameLine* bottom = static_cast<GameLine*>(bottomOutline);
		bottom->SetPosition(newStartPoint, newEndPoint);
		bottom->Update();
	}
#endif
}

void Player::InputActionNotify(const InputEventBatch& inputBatch)
{
	hasObjectMovedThisFrame = false;
	int const batchSize = inputBatch.getDataBatchSize();
	if (batchSize > 0)
	{
		for (int i = 0; i < batchSize; ++i)
		{
			const DataBindingWrapper* wrapper = inputToActionBindings->GetBinding(inputBatch.getDataAtIndex(i));
			if (wrapper == nullptr)
				continue;

			if (inputBatch.getDataAtIndex(i).status == KEYBOARD_BUTTON_PRESS)
			{
				if (wrapper->action == Actions::Game::GAME_EXIT)
				{
					GameStateManager::PushState(new GameStateMainMenu);
					// Once we got the exit action we don't need to
					// check for the other actions
					break;
				}
				else if (wrapper->action < Actions::Gameplay::GAMEPLAY_COUNT && m_action_handler[wrapper->action])
				{
					void (Player::*handle_event)(void* extraData) = m_action_handler[wrapper->action];
					if (handle_event)
						(this->*(handle_event))(wrapper->extraData.get());
				}
			}
			else if (inputBatch.getDataAtIndex(i).status == KEYBOARD_BUTTON_RELEASE)
			{
				if (wrapper->action == Actions::Gameplay::GAMEPLAY_MOVE_DOWN || wrapper->action == Actions::Gameplay::GAMEPLAY_MOVE_UP ||
					wrapper->action == Actions::Gameplay::GAMEPLAY_MOVE_LEFT || wrapper->action == Actions::Gameplay::GAMEPLAY_MOVE_RIGHT)
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

void Player::OnMovement(void* extraData)
{
	speedGoal = PLAYER_SPEED_GOAL;
	hasObjectMovedThisFrame = true;

	// We know that at this point we have extraData
	ComputeDirection((vec_3x*)extraData);
	SetFlagON(OBJECT_IS_MOVING);
}

void Player::ComputeDirection(const vec_3x* newOrientation)
{
	vector::vector_3x::Addition(newDirection, newDirection, *newOrientation);
}

void Player::UpdateMovement(float framesElapsedTime)
{
	vec_3x directionAndSpeed;
	currentSpeed = Motion::MotionInterpolation(speedGoal, currentSpeed, framesElapsedTime * DELTA_TIME_BOOST);
	vector::vector_3x::DotProduct(directionAndSpeed, currDirection, currentSpeed * framesElapsedTime);
	vector::vector_3x::Addition(m_world_position, m_world_position, directionAndSpeed);
}
