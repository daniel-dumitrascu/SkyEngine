#pragma once
#include "loader/Loader.h"
#include "logging/Logging.h"
#include "SettingsPackage.h"
#include <memory>

class SettingsLoader : public Loader
{
public:

	static SettingsLoader* GetInstance();
	void* Load(const std::string& file_path);
	std::string GetValue(std::string key);

private:

	SettingsLoader();
	SettingsLoader(const SettingsLoader& copy) = delete;
	~SettingsLoader() {};

	SettingsLoader& operator = (const SettingsLoader& copy) = delete;

private:

	std::unique_ptr<SettingsPackage> settingsPackage;
	Logging log;
};