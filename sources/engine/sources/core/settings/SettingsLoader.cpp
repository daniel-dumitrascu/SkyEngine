#include "SettingsLoader.h"
#include "utils/Utils.h"
#include "parser/FileSettings.h"

SettingsLoader* SettingsLoader::GetInstance()
{
	static SettingsLoader instance;
	return &instance;
}

SettingsLoader::SettingsLoader() : log("SettingsLoader"), settingsPackage(nullptr)
{
}

void* SettingsLoader::Load(const std::string& file_path)
{
	std::string extension = utils::str::GetFileExtension(file_path);

	if (extension != "json")
	{
		log.message("The extension of the settings file is invalid: " + file_path, Logging::MSG_ERROR);
		exit(1);
	}

	FileSettings* parser = FileSettings::GetInstance();

	if (settingsPackage != nullptr)
		settingsPackage.reset();

	settingsPackage = std::unique_ptr<SettingsPackage>(parser->ParseFile(file_path));
	return reinterpret_cast<void*>(settingsPackage.get());
}

std::string SettingsLoader::GetValue(std::string key)
{
	if (settingsPackage == nullptr)
		return "";

	auto ite = settingsPackage->data.find(key);
	if (ite == settingsPackage->data.end())
		return "";

	return ite->second;
}