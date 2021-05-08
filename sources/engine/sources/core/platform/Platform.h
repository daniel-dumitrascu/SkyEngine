#ifndef SUPPORTED_PLATFORM
#define SUPPORTED_PLATFORM

#include "global/GlobalData.h"

class Platform
{
	public:

		Platform();
		virtual ~Platform();

		virtual void InitPlatform(void** screen_handle) = 0;
		virtual void UpdatePlatform() = 0;
		virtual bool IsRunning() = 0;

		static unsigned int const GetWindowWidth() { return m_resolution.width; }
		static unsigned int const GetWindowHeight() { return m_resolution.height; }
		static const AspectRatio GetWindowAspectRatio() { return m_aspect_ratio; } 
		static const DisplayResolution GetWindowResolution() { return m_resolution; }

		void SetWindowAspectRatio(const AspectRatio& aspect_ratio);
		void SetWindowResolution(const DisplayResolution& resolution);

	protected:

		virtual void LoadPlatformSettings() = 0;

		static Platform* m_platform;
		static AspectRatio m_aspect_ratio;
		static DisplayResolution m_resolution;

		void* m_window;
};



#endif