#pragma once

#include <string>

struct GLFWwindow;

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool ShouldClose() const;

	void SwapBuffers();
	void PollEvents();

	int GetWidth() const { return m_width; };
	int GetHeight() const { return m_height; };

	GLFWwindow* GetNativeHandle() const { return m_window; };

private:
	void InitGLFW();
	void InitGLAD();

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window = nullptr;
	int m_width = 0;
	int m_height = 0;
};