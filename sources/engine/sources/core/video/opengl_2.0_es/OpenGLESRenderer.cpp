#if(GRAPHICS_OPENGL_ES_2_0 == 1)
#include <vector>
#include "OpenGLESRenderer.h"
#include "utils/Utils.h"
#include "utils/DebugOutput.h"


Renderer* OpenGLRenderer::GetHandle()
{
	if (!m_handle)
		m_handle = new OpenGLESRenderer;
	
	return m_handle;
}

OpenGLESRenderer::OpenGLESRenderer()
{
	
}

OpenGLESRenderer::~OpenGLESRenderer()
{ 
	delete m_handle;
	m_handle = NULL;
}

void OpenGLESRenderer::InitRenderer(void* screen_handle,
	                               const AspectRatio& aspect_ratio,
								   const DisplayResolution& resolution)
{
	AppInfo << "OpenGL ES 2.0 init" << std::endl;


	/*TODO how are those atrib got in other games?*/
	/*TODO don't like that this values are hardcoded*/
	/*TODO check on the triangle example what are the roles of these atribs and how to pass them around*/
	EGLint attribList[] =
	{
		EGL_NATIVE_RENDERABLE, EGL_FALSE,
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, 0,
		EGL_DEPTH_SIZE, 24,
		EGL_STENCIL_SIZE, 8,
		EGL_SAMPLE_BUFFERS, 1,
		EGL_SAMPLES, 4,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};

	if (!CreateContext((EGLNativeWindowType)screen_handle, attribList))
		throw std::string("can't create the application context.");

	/* Calculating the aspect ratio */
	int viewport_width = resolution.width;
	int viewport_height = (resolution.width / aspect_ratio.x) * aspect_ratio.y;

	int viewport_start_x = 0;
	int viewport_start_y = (resolution.height / 2) - (viewport_height / 2);

	glViewport(viewport_start_x, viewport_start_y, viewport_width, viewport_height);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //TODO play with different values here, maybe you can find a better quality

	glClearDepthf(1.0f); /*TODO - runs faster if I comment this line or if I add the value 0.0f ? Must be tested */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLESRenderer::Render()
{
	/*TODO don't do SwapBuffers at every draw. Only after all the scene objects have been drawn glDrawArrays */
	eglSwapBuffers(display, surface);
}

bool OpenGLESRenderer::CreateContext(EGLNativeWindowType hWnd, EGLint attribList[])
{
	// Get Display
#if(WINDOWS_PLATFORM)
	display = eglGetDisplay(GetDC(hWnd));
#endif
   if(display == EGL_NO_DISPLAY)
      return false;

   EGLint majorVersion;
   EGLint minorVersion;

   // Initialize EGL
   if(!eglInitialize(display, &majorVersion, &minorVersion))
      return false;

   EGLint numConfigs;

   // Get configs
   if(!eglGetConfigs(display, NULL, 0, &numConfigs))
      return false;

   EGLConfig config;

   //Choose config
   if(!eglChooseConfig(display, attribList, &config, 1, &numConfigs))
      return false;
   
   // Create a surface
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
   if(surface == EGL_NO_SURFACE)
      return false;
   
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

   // Create a GL context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
   if(context == EGL_NO_CONTEXT)
      return false;
   
   // Make the context current
   if(!eglMakeCurrent(display, surface, surface, context))
      return false;
   
   return true;
}

#endif //GRAPHICS_OPENGL_ES_2_0