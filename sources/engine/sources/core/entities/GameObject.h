#ifndef OBJECT_H
#define OBJECT_H

#include "math/Matrix.h"
#include "shaders/ShaderResources.h"
#include "level/LevelData.h"
#include "primitive/Rectangle.h"
#include "../input/Controllable.h"
#include "utils/BinaryArray.h"

#include <array>
#include <memory>

enum GameObjectFlags
{
	OBJECT_IS_MOVING,
	OBJECT_IS_CONTROLLABLE,
	OBJECT_IS_RENDERABLE,
	OBJECT_IS_COLLIDABLE,
	OBJECT_IS_ANIMATED,

	OBJECT_FLAG_COUNT
};


class WireFrame;
struct Texture;
class Rectangle;
class Tile;

class GameObject : public Controllable
{
	public:

		//TODO rotation should be passes also
		GameObject(	WireFrame* wireframe, 
					Texture* texture, 
					int shader, 
					const float posX,
					const float posY,
					const int scale,
					const std::string& id,
					InputHandleProfile layer );

		virtual ~GameObject();

		// Because of the GameObjectLabel which must be unique we don't use a 
		// copy constructor anymore but the clone method in the Factory class.
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		// Easy method for cloning a GameObject.
		// Be careful, this allocates memory for the new object
		virtual std::unique_ptr<GameObject> Clone();

		void SetScale(const int scale);
		int GetScale() const;
		void SetPosition(float pos_x, float pos_y);
		vec_2x GetPosition() const;
		void SetRotation(float rot_x, float rot_y);
		vec_2x GetRotation() const;

		virtual void Draw() = 0;
		virtual void PreDraw() = 0;
		virtual void Update() = 0;
		virtual void InputActionNotify(const InputEventBatch& inputBatch) {};

		bool IsAlive() { return m_destroy; };
		bool IsFlagON(GameObjectFlags flag);
		void SetFlagON(GameObjectFlags flag);
		void SetFlagOFF(GameObjectFlags flag);
		Rectangle GetObjectWorldRect();
		const std::array<int, 4>& GetOccupiedGriDArea() const { return m_occupiedGridArea; }
		void SetOccupiedGridArea(int topIndex, int leftIndex, int bottomIndex, int rightIndex);
		const std::string GetID() const { return m_id; }

		void AddCollidingNeighbour(GameObject* neighbour);
		void RemoveCollidingNeighbour(GameObject* neighbour);
		void ClearCollidingNeighbours();
		const std::map<const std::string, GameObject*>& GetCollidingNeighbours() const;

#if(DEBUG_SECTION)
		void SetOutline(bool value) { isOutlineEnabled = value; }
#endif

	protected:

		float m_rectHeight;
		float m_rectLenght;	
		int m_shader;							// The shader used by this entity     //TODO we don't need a m_shader in each entity. This should be at the game level or entity collection management
		BinaryArray m_gameObjectSettings;
		WireFrame* m_wireframe;					// The mesh model of the entity
		Rectangle* m_rectangle = nullptr;		// The rect constr from the wireframe used in collision calc
		Texture* m_texture;						// The texture applied on the mesh
		std::array<int, 4> m_occupiedGridArea;	// The last known occupied grid area of the object
		std::string	m_id;						// The unique identifier in the game of this object

		vec_3x m_world_position;
		vec_3x m_world_rotation;
		mat_4x m_world_matrix;
		mat_4x m_wp_matrix;

		std::map<const std::string, GameObject*> m_collidingNeighbours;

		int  m_scaling;
		bool m_destroy;

#if(DEBUG_SECTION)
		bool isOutlineEnabled = true;	// Debug option that will draw a rectangle around the object
#endif
};

#endif