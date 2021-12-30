#pragma once
#include "stream/Stream.h"
#include "../SettingsPackage.h"

class FileSettings : private Stream
{
public:

	static FileSettings* GetInstance();
	SettingsPackage* ParseFile(const std::string& file_path);

private:

	FileSettings() {};
	FileSettings(const FileSettings& copy) {};
	~FileSettings() {};
};