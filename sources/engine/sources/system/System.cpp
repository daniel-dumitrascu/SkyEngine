#include "System.h"
#include "global/GlobalPaths.h"
#include "utils/Utils.h"
#include "global/GlobalData.h"
#include "settings/SettingsLoader.h"
#include "nlohmann/json.hpp"

#include <fstream>

using json = nlohmann::json;

Application*  System::m_app = NULL;


System* System::GetSystem()
{
	static System m_instance;
	return &m_instance;
}

void System::SetApplication(Application* const app, const std::string title)
{ 
	m_app = app;
	if (m_app == nullptr)
	{
		log.message("Application could not be initiated.", Logging::MSG_ERROR);
		exit(1);
	}

	m_title = utils::str::Strfmt("%s - built on %s %s, version 0.001", title.c_str(), __TIME__, __DATE__);
}

System::System() : m_title(""), log("System")
{
	ConstrSystemGlobals();
	CreateSettingsFileIfNonExisting(working_dir_path);
	SettingsLoader::GetInstance()->Load(working_dir_path + "/settings.json");
}

void System::Init() 
{ 
	m_driver = std::make_unique<Driver>();
	if (m_driver == nullptr)
	{
		log.message("System driver could not be initiated.", Logging::MSG_ERROR);
		exit(1);
	}

	m_driver->InitDriver();
	m_app->Init();
}

void System::Run() 
{ 
	global_timer.Start();

	int updates = 0, frames = 0;
	signed long long timer = CoreTime::GetTime();

	while (m_driver->IsRunning() && m_app->IsRunning())
	{
		if (global_timer.IsExceeded())
		{
			m_driver->Update();    /* update the platform interactions and graphics settings */
			m_app->Update();	   /* update a game frame */
			m_app->Draw();	       /* draw a game frame */
			m_driver->Render();    /* render the frame */

			updates++;
		}

		frames++;

		//TODO debug
		if ((CoreTime::GetTime() - timer) > SECOND_IN_MILISEC)
		{
			timer += SECOND_IN_MILISEC;
			//log.message(std::string("Rendered frames per second: ") + std::to_string(updates) + std::string("    Total frames per second: ") + std::to_string(frames), Logging::MSG_DEBUG);
			updates = 0;
			frames = 0;
		}
	} 
}

void System::Close()
{ 
	m_app->Close(); 
}

void System::ConstrSystemGlobals()
{
	utils::path::GetWorkingDir(working_dir_path);
}

void System::CreateSettingsFileIfNonExisting(const std::string& working_dir_path)
{
	if (!utils::path::IsFileCreated(working_dir_path, "settings.json"))
		CreateDefaultSettingsFile(working_dir_path, "settings.json");	
}

void System::CreateDefaultSettingsFile(const std::string& _path, const std::string& _fileName)
{
	std::ofstream settingFile = utils::path::CreateFileAtLocation(_path, _fileName);

	json settingsJson;
	settingsJson["defaultResources"]["splashScreen"]["texture"] = "assets/textures/default/splashscreen/splashscreen.png";
	settingsJson["defaultResources"]["splashScreen"]["mesh"] = "assets/meshes/default/splashscreen/splashscreen.mesh";
	settingsJson["defaultResources"]["splashScreen"]["shader"] = "assets/shaders/default/basic";

	settingsJson["defaultResources"]["menu"]["mesh"] = "assets/meshes/default/menu/main_menu.mesh";
	settingsJson["defaultResources"]["menu"]["texture"] = "assets/textures/default/menu/main_menu.png";	
	settingsJson["defaultResources"]["menu"]["shader"] = "assets/shaders/default/basic";

	std::string strJson = settingsJson.dump(4);

	settingFile.write(strJson.c_str(), strJson.length());
	settingFile.flush();
	settingFile.close();
}