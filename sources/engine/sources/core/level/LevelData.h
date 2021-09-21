#ifndef LEVEL_DATA
#define LEVEL_DATA

#include <iostream>
#include <list>
#include "../math/Vector.h"

struct GameObjectPackage
{
	GameObjectPackage() :	m_renderable(false),
							m_collidable(false),
							m_controllable(false),
							m_id(""),
							m_type(0),
							m_meshID(0),
							m_animationID(0),
							m_textureID(0),
							m_shaderID(0),
							m_scale(0),
							m_thickness(0)
	{
		vector::vector_2x::SetVector(m_startPoint, 0.0f, 0.0f);
		vector::vector_2x::SetVector(m_endPoint, 0.0f, 0.0f);
		vector::vector_2x::SetVector(m_pointTopLeft, 0.0f, 0.0f);
		vector::vector_2x::SetVector(m_pointBottomRight, 0.0f, 0.0f);
		vector::vector_3x::SetVector(m_position, 0.0f, 0.0f, 0.0f);
		vector::vector_3x::SetVector(m_rotation, 0.0f, 0.0f, 0.0f);
		vector::vector_4x::SetVector(m_color, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	bool m_renderable;
	bool m_collidable;
	bool m_controllable;
	std::string m_id;
	int m_type;
	int m_meshID;
	int m_animationID;
	int m_textureID;
	int m_shaderID;
	int m_scale;
	int m_thickness;		// valid only for line objects
	vec_2x m_startPoint;	// valid only for line objects
	vec_2x m_endPoint;		// valid only for line objects
	vec_2x m_pointTopLeft;		// valid only for rect objects
	vec_2x m_pointBottomRight;	// valid only for rect objects
	vec_3x m_position;
	vec_3x m_rotation;
	vec_4x m_color;
};

struct LevelPackage
{
	std::list<GameObjectPackage> m_level_data;
};

#endif