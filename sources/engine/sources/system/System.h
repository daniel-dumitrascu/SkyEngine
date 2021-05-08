#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
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

		bool CleanUp();
		void ConstrSystemGlobals();

		std::string    m_title;
		Driver*        m_driver;
		Logging		   log;

	protected:

		static Application*   m_app;
};



#endif