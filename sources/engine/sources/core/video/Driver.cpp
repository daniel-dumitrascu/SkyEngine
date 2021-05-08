#include "Driver.h"
#include "../utils/Utils.h"

/* For what platform are we compilling ? */
#if(WINDOWS_PLATFORM)	
	#include "../platform/windows/WindowsPlatform.h"
	//TODO #include "../platform/windows/WindowsDefines.h"
#elif(LINUX_PLATFORM)
	#include "../platform/linux/LinuxPlatform.h"
#endif

/* The painting library used */
#if(GRAPHICS_OPENGL_ES_2_0)
	#include "opengl_2.0_es/OpenGLESRenderer.h"
#elif(GRAPHICS_OPENGL_LATEST)
	#include "opengl_latest/OpenGLLatestRenderer.h"
#endif



Driver::Driver() : screen_handle(NULL), log("Driver")
{
	try
	{
		/* Initiate the platform */
#if(WINDOWS_PLATFORM)		
		m_supported_platform = WindowsPlatform::GetPlatformHandle();
#elif(LINUX_PLATFORM)
		m_supported_platform = LinuxPlatform::GetPlatformHandle();
#elif(ANDROID_PLATFORM)
		m_supported_platform = AndroidPlatform::GetPlatformHandle();
#elif(iOS_PLATFORM)
		m_supported_platform = iOSPlatform::GetPlatformHandle();
#elif(PS4_PLATFORM)
		m_supported_platform = PS3Platform::GetPlatformHandle();
#endif		

	}
	catch (const std::string& catch_err)
	{
		log.message("Platform can not be initiated: " + catch_err, Logging::MSG_ERROR);
		exit(1);
	}

	
	try
	{
		/* Here, we initiate the graphics library used for drawing */
#if(GRAPHICS_OPENGL_ES_2_0)
		m_supported_render = OpenGLESRenderer::GetHandle();
#elif(DIRECTX_GRAPHICS)
		m_supported_render = DirectXGraphics::GetGraphicsHandle();
#elif(GRAPHICS_OPENGL_LATEST)
		m_supported_render = OpenGLLatestRenderer::GetHandle();
#endif
	}
	catch (const std::string& catch_err)
	{
		log.message("Graphics library can not be initiated: " + catch_err, Logging::MSG_ERROR);
		exit(1);
	}
}

Driver::~Driver()
{

}

void Driver::InitDriver()
{
#if(GRAPHICS_OPENGL_LATEST)
	if (!glfwInit())
		exit(-1);
#endif
	m_supported_platform->InitPlatform(&screen_handle);
	m_supported_render->InitRenderer(screen_handle, Platform::GetWindowAspectRatio(), Platform::GetWindowResolution());
}

void Driver::Update()
{
	m_supported_platform->UpdatePlatform();
}

void Driver::Render()
{
	m_supported_render->Render();
}