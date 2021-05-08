#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// An array of 3 vectors which represents 3 vertices
static GLfloat g_vertex_buffer_data[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

#if(GRAPHICS_OPENGL_LATEST)
	if (glewInit() != GLEW_OK)
		std::cout << "Error during glew initialization" << std::flush;
	else
		std::cout << "Glew has been initiated: " << glGetString(GL_VERSION) << std::flush;
#endif

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // pink

#if(GRAPHICS_OPENGL_1_1)
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
#elif(GRAPHICS_OPENGL_LATEST)
		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
								0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
								3,                  // size
								GL_FLOAT,           // type
								GL_FALSE,           // normalized?
								0,                  // stride
								(void*)0            // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
#endif

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch(key)
	{
		/* Keyboard update */
		case GLFW_KEY_RIGHT:
		{
			g_vertex_buffer_data[0] += 0.01;
			g_vertex_buffer_data[3] += 0.01;
			g_vertex_buffer_data[6] += 0.01;
			break;
		}
		case GLFW_KEY_LEFT:
		{
			g_vertex_buffer_data[0] -= 0.01;
			g_vertex_buffer_data[3] -= 0.01;
			g_vertex_buffer_data[6] -= 0.01;
			break;
		}
		case GLFW_KEY_DOWN:
		{
			g_vertex_buffer_data[1] -= 0.01;
			g_vertex_buffer_data[4] -= 0.01;
			g_vertex_buffer_data[7] -= 0.01;
			break;
		}
		case GLFW_KEY_UP:
		{
			g_vertex_buffer_data[1] += 0.01;
			g_vertex_buffer_data[4] += 0.01;
			g_vertex_buffer_data[7] += 0.01;
			break;
		}
		case GLFW_KEY_1:
		{
			std::cout << "Tasta 1 a fost apasata." << std::endl;
			break;
		}
		case GLFW_KEY_ESCAPE:
		{
			std::cout << "Tasta esc a fost apasata." << std::endl;
			break;
		}
	}

	// Send the data to OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			std::cout << "Mouse left clik button" << std::endl;
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			std::cout << "Mouse right clik button" << std::endl;
			break;
		}
	}	
}