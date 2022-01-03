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
	if (Level_elem == nullptr)
	{
		return nullptr;
	}

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
				const char* stringRawValue;
				result += Property_elem->QueryIntAttribute("Type", &(game_object_pack.m_type));
				result += Property_elem->QueryStringAttribute("ResourceMeshPath", &stringRawValue);
				game_object_pack.m_meshPath = stringRawValue;
				result += Property_elem->QueryStringAttribute("ResourceTexturePath", &stringRawValue);
				game_object_pack.m_texturePath = stringRawValue;
				result += Property_elem->QueryStringAttribute("ResourceShaderPath", &stringRawValue);
				game_object_pack.m_shaderPath = stringRawValue;
				result += Property_elem->QueryStringAttribute("ResourceAnimationPath", &stringRawValue);

				// An animation resource is not mandatory, so, we can reset
				// the error variable if the attribute is not found
				if (result == tinyxml2::XML_NO_ATTRIBUTE)
					result = 0;

				game_object_pack.m_animationPath = stringRawValue;
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

			// Parse the Z-Buffer
			Property_elem = Property_elem->NextSiblingElement("ZBuffer");

			if (Property_elem)
				result += Property_elem->QueryIntAttribute("value", &(game_object_pack.m_zBuffer));

			if (result != tinyxml2::XML_SUCCESS)
				return NULL;

			// Add entity data to the level data 
			level->m_level_data.push_back(game_object_pack);
		}
		else
			return NULL;

		object_elem = object_elem->NextSiblingElement("GameObject");
	}

	tinyxml2::XMLElement* cameras_elem = Level_elem->FirstChildElement("Cameras");
	if (cameras_elem == nullptr)
	{
		return nullptr;
	}

	tinyxml2::XMLElement* camera_elem = cameras_elem->FirstChildElement("Camera");

	while (camera_elem != nullptr)
	{
		CameraPackage camera_pack;
		const char* id;
		result += camera_elem->QueryStringAttribute("id", &id);

		// Check the result before using the id
		if (result != tinyxml2::XML_SUCCESS)
			return NULL;

		camera_pack.camera_id = std::string(id);

		tinyxml2::XMLElement* property_elem = camera_elem->FirstChildElement("Position");
		if (property_elem)
		{
			result += property_elem->QueryFloatAttribute("x", &(camera_pack.position.elem[0]));
			result += property_elem->QueryFloatAttribute("y", &(camera_pack.position.elem[1]));
		}

		property_elem = camera_elem->FirstChildElement("Rotation");
		if (property_elem)
		{
			result += property_elem->QueryFloatAttribute("x", &(camera_pack.rotation.elem[0]));
			result += property_elem->QueryFloatAttribute("y", &(camera_pack.rotation.elem[1]));
		}

		if (result != tinyxml2::XML_SUCCESS)
			return NULL;

		level->m_level_cameras.push_back(camera_pack);
		camera_elem = camera_elem->NextSiblingElement("Camera");
	}

	tinyxml2::XMLElement* active_camera_elem = Level_elem->FirstChildElement("SelectedActiveCamera");
	if (active_camera_elem)
	{
		const char* value;
		result += active_camera_elem->QueryStringAttribute("CameraID", &(value));
		level->m_active_camera_id = std::string(value);

		result += active_camera_elem->QueryStringAttribute("AttachedObject", &(value));
		level->m_active_camera_attached_object = std::string(value);		

		if (result != tinyxml2::XML_SUCCESS)
			return NULL;
	}

	return level;
}
