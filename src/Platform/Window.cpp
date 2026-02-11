#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window* Window::s_main = nullptr;

Window::Window(int width, int height, const std::string& title)
	: m_width(width), m_height(height)
{
	InitGLFW();

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	s_main = this;

	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();

		std::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);

	InitGLAD();

	glViewport(0, 0, width, height);

}

Window::~Window()
{
	if (s_main == this) s_main = nullptr;
	glfwDestroyWindow(m_window);
	glfwTerminate();
}


Window* Window::Main()
{
	return s_main;
}

void Window::InitGLFW()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		std::exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::InitGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		std::exit(EXIT_FAILURE);
	}
}


bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}


void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (!self)
		return;

	self->m_width = width;
	self->m_height = height;

	glViewport(0, 0, width, height);
}





