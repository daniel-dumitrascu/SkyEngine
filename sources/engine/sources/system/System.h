#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <memory>
#include "../core/video/Driver.h"
#include "../application/Application.h"
#include "logging/Logging.h"

class System
{
	public:

		static System* GetSystem();
		static Application* GetApp() { return m_app; };

		void SetApplication(Application* const app, const std::string title);

		void Init();
		void Run();
		void Close();

	private:

		System();
		System(const System& copy) = delete;
		~System() {};

		System& operator=(const System& copy) {};

		void ConstrSystemGlobals();
		void CreateSettingsFileIfNonExisting(const std::string& working_dir_path);
		void CreateDefaultSettingsFile(const std::string& _path, const std::string& _fileName);

		std::string					m_title;
		std::unique_ptr<Driver>     m_driver;
		Logging						log;

	protected:

		static Application*   m_app;
};



#endif