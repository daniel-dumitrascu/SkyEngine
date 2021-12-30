#include "FileSettings.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

FileSettings* FileSettings::GetInstance()
{
	static FileSettings instance;
	return &instance;
}

SettingsPackage* FileSettings::ParseFile(const std::string& file_path)
{
	SettingsPackage* settings = new SettingsPackage();

	// Open the file
	Open(file_path, std::ios::in | std::ios::binary);

	// Read the whole file into memory
	std::string model_buffer(m_file_size, ' ');
	Read(&model_buffer[0], m_file_size);

	// Close the file stream 
	Close();

	json settingsJson = json::parse(model_buffer);
	
	settings->data.insert(std::pair<std::string, std::string>("defaultResources.splashScreen.mesh", 
		settingsJson["defaultResources"]["splashScreen"]["mesh"]));
	settings->data.insert(std::pair<std::string, std::string>("defaultResources.splashScreen.name",
		settingsJson["defaultResources"]["splashScreen"]["name"]));
	settings->data.insert(std::pair<std::string, std::string>("defaultResources.splashScreen.path",
		settingsJson["defaultResources"]["splashScreen"]["path"]));
	
	return settings;
}