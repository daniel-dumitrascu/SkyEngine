#include "ResourceKeyCollection.h"


ResourceKeyCollection* ResourceKeyCollection::GetInstance()
{
	static ResourceKeyCollection instance;
	return &instance;
}

void ResourceKeyCollection::AddKey(const int key_type, const int id, const std::string& name)
{
	if (key_type == KEY_TILE)
	{
		std::map<const int, const std::string>::const_iterator it = m_tile_keys.find(id);
		if (it == m_tile_keys.end())
		{
			m_tile_keys.insert(std::pair<const int, const std::string>(id, name));
		}
	}
	else if (key_type == KEY_ANIMATION)
	{
		std::map<const int, const std::string>::const_iterator it = m_animation_keys.find(id);
		if (it == m_animation_keys.end())
		{
			m_animation_keys.insert(std::pair<const int, const std::string>(id, name));
		}
	}
	else if (key_type == KEY_TEXTURE)
	{
		std::map<const int, const std::string>::const_iterator it = m_texture_keys.find(id);
		if (it == m_texture_keys.end())
		{
			m_texture_keys.insert(std::pair<const int, const std::string>(id, name));
		}
	}
	else if (key_type == KEY_SHADER)
	{
		std::map<const int, const std::string>::const_iterator it = m_shader_keys.find(id);
		if (it == m_shader_keys.end())
		{
			m_shader_keys.insert(std::pair<const int, const std::string>(id, name));
		}
	}
}

const std::string& ResourceKeyCollection::GetNameByKey(const int key_type, int id)
{
	if (key_type == KEY_TILE)
	{
		std::map<const int, const std::string>::const_iterator it = m_tile_keys.find(id);
		if (it != m_tile_keys.end())
			return it->second;
	}
	else if (key_type == KEY_ANIMATION)
	{
		std::map<const int, const std::string>::const_iterator it = m_animation_keys.find(id);
		if (it != m_animation_keys.end())
			return it->second;
	}
	else if (key_type == KEY_TEXTURE)
	{
		std::map<const int, const std::string>::const_iterator it = m_texture_keys.find(id);
		if (it != m_texture_keys.end())
			return it->second;
	}
	else if (key_type == KEY_SHADER)
	{
		std::map<const int, const std::string>::const_iterator it = m_shader_keys.find(id);
		if (it != m_shader_keys.end())
			return it->second;
	}

	return m_undefined;
}