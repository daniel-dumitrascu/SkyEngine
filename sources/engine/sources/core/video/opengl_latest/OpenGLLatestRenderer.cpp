#if(GRAPHICS_OPENGL_LATEST == 1)
#include <vector>
#include "OpenGLLatestRenderer.h"
#include "utils/Utils.h"
#include <iostream>



Renderer* OpenGLLatestRenderer::GetHandle()
{
	if (!m_handle)
		m_handle = new OpenGLLatestRenderer;

	return m_handle;
}

OpenGLLatestRenderer::~OpenGLLatestRenderer()
{
	delete m_handle;
	m_handle = NULL;
}

void OpenGLLatestRenderer::InitRenderer(void* screen_handle,
										const AspectRatio& aspect_ratio,
										const DisplayResolution& resolution)
{
	//TODO continue - look in main.cpp from the sample project because the current order of init (screen then video) is not correct
	log.message("OpenGL init.", Logging::MSG_INFO);

	m_screenHandle = (GLFWwindow*)screen_handle;

	/* Make the window's context current */
	glfwMakeContextCurrent(m_screenHandle);

	if (glewInit() != GLEW_OK)
		log.message("Error during glew initialization", Logging::MSG_ERROR);
	else
	{
		log.message(std::string("OpenGl version ") + reinterpret_cast<char const*>(glGetString(GL_VERSION)), Logging::MSG_ERROR);
	}

	/* Calculating the aspect ratio */
	int viewport_width = 1600; //WORLD_WIDTH;
	int viewport_height = 900; //WORLD_HEIGHT;

	int viewport_start_x = 0;
	int viewport_start_y = 0;

	glViewport(viewport_start_x, viewport_start_y, viewport_width, viewport_height);

	//glLoadIdentity();
	//glFrustum (0.0, 1.0, 0.0, 1.0, 0.1, 1000.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //TODO play with different values here, maybe you can find a better quality

	glClearDepthf(1.0f); /*TODO - runs faster if I comment this line or if I add the value 0.0f ? Must be tested */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLLatestRenderer::Render()
{
	/*TODO don't do SwapBuffers at every draw. Only after all the scene objects have been drawn glDrawArrays */
	glfwSwapBuffers(m_screenHandle);
}

#endif //GRAPHICS_OPENGL_LATEST