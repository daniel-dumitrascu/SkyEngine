#if(GRAPHICS_OPENGL_ES_2_0 == 1)
#ifndef OPENGLESRENDERER
#define OPENGLESRENDERER

#include "../GraphicHeaders.h"
#include "../Renderer.h"


//TODO Opengl should also have a LoadOpenGLSettings  function
//TODO You should check the state of glGetError (...) after each of the calls you made.
//TODO http://www.opengl.org/wiki/Example_Code exemple of glDetachShader and glDeleteShader. Poti testa acest clenup mai intai pe Qengine


class OpenGLESRenderer : public Renderer
{
	public:

		static Renderer* GetHandle();
	
		void InitRenderer(void* screen_handle,
			              const AspectRatio& aspect_ratio,
			              const DisplayResolution& resolution);
		void Render();

	private:

		OpenGLESRenderer();
		OpenGLESRenderer(const OpenGLESRenderer& copy) {};
		~OpenGLESRenderer();

		OpenGLESRenderer& operator=(OpenGLESRenderer& copy) {};

		bool CreateContext(EGLNativeWindowType hWnd, EGLint attribList[]);

	private:

		EGLDisplay    display; 
		EGLContext    context;
		EGLSurface    surface;
};

#endif //OPENGLESRENDERER
#endif //GRAPHICS_OPENGL_ES_2_0