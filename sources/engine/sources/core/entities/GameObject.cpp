#include "GameObject.h"
#include "global/GlobalData.h"
#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include "math/Vector.h"
#include "math/Geometry.h"
#include "primitive/Rectangle.h"



GameObject::GameObject( WireFrame* wireframe,
						Texture* texture, 
						int shader, 
						const float posX, 
						const float posY, 
						int scale,
						InputHandleProfile layer) : Controllable(layer),
												  m_wireframe(wireframe),
												  m_texture(texture),
												  m_shader(shader),
												  m_scaling(1),
												  m_destroy(true),
												  m_rectHeight(0.0f),
												  m_rectLenght(0.0f),
												  m_zbuffer(0.0f),
												  m_gameObjectSettings(OBJECT_FLAG_COUNT)
{
	SetFlagOFF(GameObjectFlags::OBJECT_IS_ANIMATED);

	//TODO - for now this is ok but let's say that at some point a game object will be defined as a 
	//as of rectangles all working together. All those rect will not form a rect occupied area anymore
	// Set to a default value the occupied grid area
	m_occupiedGridArea[0] = 0;
	m_occupiedGridArea[1] = 0;
	m_occupiedGridArea[2] = 0;
	m_occupiedGridArea[3] = 0;

	matrix::matrix_4x::SetIdentity(m_world_matrix);
	matrix::matrix_4x::SetIdentity(m_wp_matrix);

	SetPosition(posX, posY);

	//SetRotation(0.0f, 0.0f);	//TODO rotation not yet suporter
	//TODO this will be deleted when rotation will be supported
	/*************************************/
	m_world_rotation.elem[0] = 0.0f;
	m_world_rotation.elem[1] = 0.0f;
	m_world_rotation.elem[2] = 0.0f;
	/*************************************/

	SetScale(scale);

	// If we have a valid wireframe, 
	// then we can create the rectangle as well
	if (m_wireframe)
	{
		m_rectangle = std::unique_ptr<Rectangle>(Geometry::ConstrRectFromWireframe(*m_wireframe));

		// Once we have a rect we can now calculate the size of that rect (height and lenght)
		vec_2x rectDimensions = Geometry::CalculateRectDimensions(*m_rectangle);
		m_rectHeight = rectDimensions.elem[0];
		m_rectLenght = rectDimensions.elem[1];
	}		
}

std::unique_ptr<GameObject> GameObject::Clone()
{
	// Must be implemented in the derived object
	return nullptr;
}

void GameObject::SetScale(const int scale)
{
	if (scale <= 0)
		return;

	m_scaling = scale;

	/* Appling the new scale */
	matrix::game_matrix::SetWorldScale(m_world_matrix, m_scaling);
}

int GameObject::GetScale() const
{
	return m_scaling;
}

void GameObject::SetPosition(float pos_x, float pos_y)
{
	/* The game object position params are  */
	/* given relative to game world			*/
	vector::vector_3x::SetVector(m_world_position, pos_x, pos_y, 0.0);
	matrix::game_matrix::SetWorldPosition(m_world_matrix, m_world_position);
}

vec_2x GameObject::GetPosition() const
{
	vec_2x pos;
	pos.elem[0] = m_world_position.elem[0]; // x
	pos.elem[1] = m_world_position.elem[1]; // y

	return pos;
}

void GameObject::SetRotation(float rot_x, float rot_y)
{
	vector::vector_3x::SetVector(m_world_rotation, rot_x, rot_y, 0.0);
	matrix::game_matrix::SetWorldRotation(m_world_matrix, m_world_rotation);
}

vec_2x GameObject::GetRotation() const
{
	vec_2x rot;
	rot.elem[0] = m_world_rotation.elem[0]; // rotation on x
	rot.elem[1] = m_world_rotation.elem[1]; // rotation on y

	return rot;
}

bool GameObject::IsFlagON(GameObjectFlags flag)
{
	return m_gameObjectSettings.IsFlagON(flag);
}

void GameObject::SetFlagON(GameObjectFlags flag)
{
	m_gameObjectSettings.SetFlagON(flag);
}

void GameObject::SetFlagOFF(GameObjectFlags flag)
{
	m_gameObjectSettings.SetFlagOFF(flag);
}

void GameObject::SetOccupiedGridArea(int topIndex, int leftIndex, int bottomIndex, int rightIndex)
{
	m_occupiedGridArea[0] = topIndex;		// topIndex
	m_occupiedGridArea[1] = leftIndex;		// leftIndex
	m_occupiedGridArea[2] = bottomIndex;	// bottomIndex
	m_occupiedGridArea[3] = rightIndex;		// rightIndex
}

Rectangle GameObject::GetObjectWorldRect()
{
	// We calculate the game object rect positioned in the game world

	vec_2x pos = GetPosition();
	float semiObjRectHeight = m_rectHeight / 2;
	float semiObjRectWidth = m_rectLenght / 2;
		
	//TODO - here we should also apply the rotation
	float top = pos.elem[1] + (semiObjRectHeight * m_scaling);	
	float left = pos.elem[0] - (semiObjRectWidth * m_scaling);	
	float bottom = pos.elem[1] - (semiObjRectHeight * m_scaling);	
	float right = pos.elem[0] + (semiObjRectWidth * m_scaling);

	return Rectangle(vec_2x(left, top), vec_2x(right, bottom));
}

void GameObject::AddCollidingNeighbour(GameObject* neighbour)
{
	if (m_collidingNeighbours.find(neighbour->GetID()) == m_collidingNeighbours.end())
	{
		m_collidingNeighbours.insert(std::pair<int, GameObject*>(neighbour->GetID(), neighbour));
	}
}

void GameObject::RemoveCollidingNeighbour(GameObject* neighbour)
{
	m_collidingNeighbours.erase(neighbour->GetID());
}

void GameObject::ClearCollidingNeighbours()
{
	std::map<const int, GameObject*>::iterator ite = m_collidingNeighbours.begin();
	for (; ite != m_collidingNeighbours.end(); ite++)
	{
		ite->second->RemoveCollidingNeighbour(this);
	}

	m_collidingNeighbours.clear();
}

const std::map<const int, GameObject*>& GameObject::GetCollidingNeighbours() const
{
	return m_collidingNeighbours;
}

#if(DEBUG_SECTION)
void GameObject::SetDebugOutlines(GameObject *leftOutline, GameObject *rightOutline, GameObject *topOutline, GameObject *bottomOutline)
{
	this->leftOutline = leftOutline;
	this->rightOutline = rightOutline;
	this->topOutline = topOutline;
	this->bottomOutline = bottomOutline;
}
#endif