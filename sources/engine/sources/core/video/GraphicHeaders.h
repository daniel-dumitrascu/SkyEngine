#pragma once

#if(GRAPHICS_OPENGL_ES_2_0 == 1)
	#include <opengl_2.0_es/include/GLES2/gl2.h>
	#include <opengl_2.0_es/include/EGL/egl.h>
#elif(GRAPHICS_OPENGL_LATEST == 1)
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif