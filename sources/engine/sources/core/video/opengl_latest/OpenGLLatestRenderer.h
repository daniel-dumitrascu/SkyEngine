#if(GRAPHICS_OPENGL_LATEST == 1)
#pragma once
#include "../GraphicHeaders.h"
#include "../Renderer.h"
#include "../../logging/Logging.h"


//TODO Opengl should also have a LoadOpenGLSettings  function
//TODO You should check the state of glGetError (...) after each of the calls you made.
//TODO http://www.opengl.org/wiki/Example_Code examples ofglDetachShader and glDeleteShader


class OpenGLLatestRenderer : public Renderer
{
public:

	static Renderer* GetHandle();

	void InitRenderer(void* screen_handle,
		const AspectRatio& aspect_ratio,
		const DisplayResolution& resolution);
	void Render();

private:

	OpenGLLatestRenderer() : log("OpenGLLatestRenderer") {}
	OpenGLLatestRenderer(const OpenGLLatestRenderer& copy) : log("OpenGLLatestRenderer") {};
	~OpenGLLatestRenderer();

	OpenGLLatestRenderer& operator=(OpenGLLatestRenderer& copy) {};

private:

	Logging log;
	GLFWwindow* m_screenHandle = nullptr;
};

#endif //GRAPHICS_OPENGL_LATEST