#include "Application.h"
#include "Platform/Window.h"
#include "Scene/SceneManager.h"
#include "Core/Time.h"
#include <glad/glad.h>

Application::Application()
{
}

void Application::Run()
{
    Window window(1280, 720, "OpenGL Engine");

    SceneManager::LoadInitialScene();

    while (!window.ShouldClose())
    {
        Time::Update();

        SceneManager::Update();

        glClearColor(0.08f, 0.10f, 0.14f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        SceneManager::Render();

        window.SwapBuffers();
        window.PollEvents();
    }
}