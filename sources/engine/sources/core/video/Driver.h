#ifndef DRIVER_H
#define DRIVER_H

#include "../platform/Platform.h"
#include "Renderer.h"
#include "logging/Logging.h"


class Driver
{
	public:

		Driver();
		Driver(const Driver& copy) = delete;
		~Driver();

		Driver& operator=(const Driver& copy) = delete;

		void InitDriver();
		void Update();
		void Render();

		bool IsRunning() { return m_supported_platform->IsRunning(); }

	private:

		void* screen_handle;

		Platform* m_supported_platform;
		Renderer* m_supported_render;
		Logging log;
};



#endif