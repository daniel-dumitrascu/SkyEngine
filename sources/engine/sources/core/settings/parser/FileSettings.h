#pragma once
#include "stream/Stream.h"
#include "../SettingsPackage.h"
#include <memory>

class FileSettings : private Stream
{
public:

	static FileSettings* GetInstance();
	std::unique_ptr<SettingsPackage> ParseFile(const std::string& file_path);

private:

	FileSettings() {};
	FileSettings(const FileSettings& copy) {};
	~FileSettings() {};
};