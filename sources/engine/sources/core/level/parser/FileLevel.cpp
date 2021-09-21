#include "FileLevel.h"
#include <tinyxml2.h>



FileLevel* FileLevel::GetInstance()
{
	static FileLevel instance;
	return &instance;
}

LevelPackage* FileLevel::ParseFile(const std::string& file_path)
{
	LevelPackage* level;
	int intValue = 0;

	/* Open the file */
	Open(file_path, std::ios::in | std::ios::binary);

	/* Read the whole file into memory */
	std::string model_buffer(m_file_size, ' ');
	Read(&model_buffer[0], m_file_size);

	/* Close the file stream */
	Close();

	/* Parse the xml document */
	tinyxml2::XMLDocument stream_doc;
	int result = 0;
	
	result = stream_doc.Parse(model_buffer.c_str());

	if (result != tinyxml2::XML_SUCCESS)
		return NULL;

	tinyxml2::XMLElement* Level_elem = stream_doc.FirstChildElement("Level");

	if (Level_elem)
	{
		level = new LevelPackage;

		tinyxml2::XMLElement* object_elem = Level_elem->FirstChildElement("GameObject");

		while (object_elem != NULL)
		{
			GameObjectPackage game_object_pack;

			if (object_elem)
			{
				const char* id;
				result += object_elem->QueryStringAttribute("id", &id);

				// Check the result before using the id
				if (result != tinyxml2::XML_SUCCESS)
					return NULL;

				game_object_pack.m_id = std::string(id);

				// Parse the composition 
				tinyxml2::XMLElement* Property_elem = object_elem->FirstChildElement("Composition");

				if (Property_elem)
				{
					result += Property_elem->QueryIntAttribute("Type", &(game_object_pack.m_type));
					result += Property_elem->QueryIntAttribute("ResourceMeshID", &(game_object_pack.m_meshID));
					result += Property_elem->QueryIntAttribute("ResourceTextureID", &(game_object_pack.m_textureID));
					result += Property_elem->QueryIntAttribute("ResourceShaderID", &(game_object_pack.m_shaderID));

					//TODO to add animation here as well
				}

				// Parse the properties 
				Property_elem = Property_elem->NextSiblingElement("Properties");

				if (Property_elem)
				{
					//XMLError.XML_NO_ATTRIBUTE
					result += Property_elem->QueryBoolAttribute("Renderable", &(game_object_pack.m_renderable));
					result += Property_elem->QueryBoolAttribute("Collidable", &(game_object_pack.m_collidable));

					// Because this property is not a mandatory one we will not add it to the result
					// So, even if this property does not exist in the level then we continue as nothing has happen
					Property_elem->QueryBoolAttribute("Controllable", &(game_object_pack.m_controllable));
				}

				// Parse the position 
				Property_elem = Property_elem->NextSiblingElement("Position");

				if (Property_elem)
				{
					result += Property_elem->QueryFloatAttribute("x", &(game_object_pack.m_position.elem[0]));
					result += Property_elem->QueryFloatAttribute("y", &(game_object_pack.m_position.elem[1]));
				}

				// Parse the rotation 
				Property_elem = Property_elem->NextSiblingElement("Rotation");

				if (Property_elem)
				{
					result += Property_elem->QueryFloatAttribute("x", &(game_object_pack.m_rotation.elem[0]));
					result += Property_elem->QueryFloatAttribute("y", &(game_object_pack.m_rotation.elem[1]));
				}

				// Parse the scale 
				Property_elem = Property_elem->NextSiblingElement("Scale");

				if (Property_elem)
					result += Property_elem->QueryIntAttribute("size", &(game_object_pack.m_scale));

				if (result != tinyxml2::XML_SUCCESS)
					return NULL;

				// Add entity data to the level data 
				level->m_level_data.push_back(game_object_pack);
			}
			else
				return NULL;

			object_elem = object_elem->NextSiblingElement("GameObject");
		}

		return level;
	}
	else
		return NULL;	
}
